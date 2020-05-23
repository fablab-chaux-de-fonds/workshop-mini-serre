#include <Arduino.h>
#include <msgpck.h>
#include <c_types.h>
#include <functional>
#include <vector>

#include "Manager.hpp"

#undef DBG_PRINT
#undef DBG_PRINTF
#undef DBG_PRINTLN

#ifdef DBG_MGR
  #define DBG_PRINT(...) { DBG_MGR.print(__VA_ARGS__); }
  #define DBG_PRINTF(...) { DBG_MGR.printf(__VA_ARGS__); }
  #define DBG_PRINTLN(...) { DBG_MGR.println(__VA_ARGS__); }
#else
  #define DBG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define DBG_PRINTF(...) {}
  #define DBG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

class DataManager : public Manager {

  public:
    void begin(const String &baseName) { _baseName = baseName; _lastUpdate = 0; }
    template <typename TType> 
    void add(String header, std::function<TType ()> functor);
    virtual void update();
    inline time_t getLastUpdate() const { return _lastUpdate; }
    inline time_t getLastFileIndex() const { return _lastFileIndex; }
  protected:
    bool parse(File &fs, const size_t &itemIndex, size_t &pos);
    bool append(File &fs, const size_t &pos, const time_t &time);
    template <typename TType>
    void writeProperty(Print *s, const String &name, TType value);
    bool parsePropertyHeader(Stream *s, const String &name);
    template <typename TType>
    bool parseProperty(Stream *s, const String &name);
    inline size_t getFileIndex(time_t utcNow) {
      return getFileIndex(DateTimeParts::from(utcNow));
    }
    virtual size_t getFileIndex(const DateTimeParts &utcPart) = 0;
    inline size_t getItemIndex(time_t utcNow) {
      return getItemIndex(DateTimeParts::from(utcNow));
    }
    virtual size_t getItemIndex(const DateTimeParts &utcPart) = 0;
    virtual time_t timebase() = 0;
    virtual size_t length() = 0;
    String _baseName;
    typedef std::function<void (Print *)> WriteFunc;
    typedef std::function<bool (Stream *)> ParseFunc;
    typedef std::pair<WriteFunc, ParseFunc> PropertyFunc;
    std::vector<PropertyFunc> _properties;
    time_t _lastUpdate;
    size_t _lastFileIndex;
};

bool DataManager::parsePropertyHeader(Stream *s, const String &name) {
  char buf[name.length()];
  return msgpck_read_string(s, buf, name.length())
    && strncmp(name.c_str(), buf, name.length());
}

template <>
void DataManager::writeProperty(Print *s, const String &name, float value) {
  msgpck_write_string(s, name);
  msgpck_write_float(s, value);
}

template <>
void DataManager::writeProperty(Print *s, const String &name, int value) {
  msgpck_write_string(s, name);
  msgpck_write_integer(s, value);
}

template <>
void DataManager::writeProperty(Print *s, const String &name, bool value) {
  msgpck_write_string(s, name);
  msgpck_write_bool(s, value);
}

template <>
void DataManager::writeProperty(Print *s, const String &name, String value) {
  msgpck_write_string(s, name);
  msgpck_write_string(s, value);
}

template <>
bool DataManager::parseProperty<float>(Stream *s, const String &name) {
  float value;
  return parsePropertyHeader(s, name) && msgpck_read_float(s, &value);
}

template <>
bool DataManager::parseProperty<int>(Stream *s, const String &name) {
  int value;
  return parsePropertyHeader(s, name) && msgpck_read_integer(s, (byte *)&value, sizeof(int));
}

template <>
bool DataManager::parseProperty<bool>(Stream *s, const String &name) {
  bool value;
  return parsePropertyHeader(s, name) && msgpck_read_bool(s, &value);
}

class NullPrint : public Print {
  public:
    virtual size_t write(uint8_t value) { _count++; return 1; }
    inline size_t count() { return _count; }
  private:
    size_t _count = 0;
};

template <>
bool DataManager::parseProperty<String>(Stream *s, const String &name) {
  NullPrint print;
  return parsePropertyHeader(s, name) && msgpck_read_string(s, &print);
}

template <typename TType> 
void DataManager::add(String header, std::function<TType ()> functor) {
  WriteFunc writeFunc = [this, header, functor](Print *s) { this->writeProperty(s, header, functor()); };
  ParseFunc parseFunc = [this, header](Stream *s) { 
    bool res = this->parseProperty<TType>(s, header); 
    if (!res) {
      DBG_PRINTF("invalid %s property\r\n", header.c_str());
    }
    return res;
  };
  PropertyFunc propertyFunc(writeFunc, parseFunc);
  _properties.push_back(propertyFunc);
}

time_t utcTime() { return DateTime.utcTime(); }

void DataManager::update() {
  
  time_t time = DateTime.utcTime();
  if (time == 0) {
    DBG_PRINTLN("Time is not valid");
    return;
  }

  size_t fileIndex = getFileIndex(time);
  time_t deltaTime = time - _lastUpdate;
  DBG_PRINTF("Delta time is %d and file index is %i, last file index was %i\r\n", deltaTime, fileIndex, _lastFileIndex);
  if (fileIndex == _lastFileIndex && _lastUpdate > 0 && deltaTime < timebase()) {
    return;
  }

  String fileName = _baseName;
  fileName.concat(fileIndex);
  DBG_PRINTF("Open %s\r\n", fileName.c_str());
  File fs = SPIFFS.open(fileName, "a+");
  if (!fs) {
    DBG_PRINTLN("error when opening file " + fileName);
    return;
  }

  size_t itemIndex = getItemIndex(time);
  size_t pos = 0;
  if (itemIndex != 0) { // Always truncate when item is zero
    if (!parse(fs, itemIndex, pos)) {
      DBG_PRINTF("Invalid file content, force truncate\r\n");
      pos = 0; // Corrupted file, truncate.
    }
  } else { 
    DBG_PRINTF("First item, force truncate.\r\n");
  }

  DBG_PRINTF("Truncate to %i\r\n", pos);
  fs.truncate(pos);

  if (pos == 0) {
    msgpck_write_array_header(&fs, length());
  }

  msgpck_write_map_header(&fs, _properties.size() + 1);
  writeProperty(&fs, "t", DateTimeParts::from(time).toString());
  for (auto property : _properties) {
    property.first(&fs);
  }

  // Complete missing record with null value in
  // order to string serialization.
  for (size_t i = itemIndex + 1; i < length(); i++) {
    msgpck_write_nil(&fs);
  }

  fs.close();

  _lastFileIndex = fileIndex;
  _lastUpdate = time;
}

bool DataManager::parse(File &fs, const size_t &itemIndex, size_t &pos) {
    size_t size;
    if (!msgpck_read_array_size(&fs, &size) || size != length()) {
      DBG_PRINTF("Invalid size %d\r\n", size);
      return false;
    }

    if (itemIndex >= size) {
      DBG_PRINTF("Invalid item index lt array size %d\r\n", itemIndex);
      return false;
    }

    for (size_t i = 0; i <= itemIndex; i++) {
      if (msgpck_map_next(&fs)) {
        u32 dataSize;
        if (!msgpck_read_map_size(&fs, &dataSize) || dataSize != _properties.size() + 1) {
          DBG_PRINTF("Invalid item map size %d\r\n", dataSize);
          return false;
        }
        if (!parseProperty<String>(&fs, "t")) {
          DBG_PRINTF("invalid t property %d\r\n", dataSize);
          return false;
        }
        for (auto property : _properties) {
          if (!property.second(&fs)) {
            return false;
          }
        }
      }
    }

    u8 next = msgpck_what_next(&fs);
    switch (next) {
      case 0xDE:
        // When a record exists after current measurement, 
        // it mean that is previous cycle record
        pos = 0; 
        break;
      case 0xFF:
      case 0xC0:
        pos = fs.position();
        break;
      default:
        return false;
    }

    return true;
}

class HourOfDayDataManager : public DataManager {
  protected:
      virtual size_t getFileIndex(const DateTimeParts &utcParts) {
        return utcParts.getHours();
      }
      virtual size_t getItemIndex(const DateTimeParts &utcParts) {
        return utcParts.getMinutes();
      }
      virtual time_t timebase() { return 60; } // every min
      virtual size_t length() { return 60; }
};

class DayOfWeekDataManager : public DataManager {
  protected:
    virtual size_t getFileIndex(const DateTimeParts &utcParts) {
      return utcParts.getWeekDay();
    }
    virtual size_t getItemIndex(const DateTimeParts &utcParts) {
      return utcParts.getHours() * 4 + utcParts.getMinutes() / 15;
    }
    virtual time_t timebase() { return 60 * 15; } // every 15 min
    virtual size_t length() { return 24 * 4; }
};

class DayOfYearDataManager : public DataManager {
  protected:
    virtual size_t getFileIndex(const DateTimeParts &utcParts) {
      return utcParts.getYearDay();
    }
    virtual size_t getItemIndex(const DateTimeParts &utcParts) {
      return utcParts.getHours();
    }
    time_t timebase() { return 60 * 60; } // every hour
    size_t length() { return 24; }
};

class WeekOfYearDataManager : public DataManager {
  protected:
    virtual size_t getFileIndex(const DateTimeParts &utcParts) {
      return utcParts.getYearDay() / 7;
    }
    virtual size_t getItemIndex(const DateTimeParts &utcParts) {
      return utcParts.getHours();
    }
    virtual time_t timebase() { return 60 * 60; } // every hour
    virtual size_t length() { return 24 * 7; }
};

class QuarterOfYearDataManager : public DayOfYearDataManager {
  protected:
    virtual size_t getFileIndex(const DateTimeParts &utcParts) {
      return utcParts.getYearDay() / 4;
    }
    virtual size_t getItemIndex(const DateTimeParts &utcParts) {
      return utcParts.getHours();
    }
    virtual time_t timebase() { return 60 * 60; } // every hour
    virtual size_t length() { return 52 / 4 * 24 * 7; }
};