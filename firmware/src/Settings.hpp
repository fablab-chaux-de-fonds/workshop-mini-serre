#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <Arduino.h>

#include <FS.h>
#include <msgpck.h>

// const String path[] PROGMEM = "/cfg";

#define DBG Serial /**< Define where debug output will be printed. */

/* Setup debug printing macros. */
#ifdef DBG
  #define DBG_PRINT(...) { DBG.print(__VA_ARGS__); }
  #define DBG_PRINTF(...) { DBG.printf(__VA_ARGS__); }
  #define DBG_PRINTLN(...) { DBG.println(__VA_ARGS__); }
#else
  #define DBG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define DBG_PRINTF(...) {}
  #define DBG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

class Settings
{
  public:
    bool setup;
    bool sta;
    String ssid;
    String passphrase;
    String path;
    String ntp;
    u8 lightSensorIndex;
    void begin(const String &path);
    void reset();
    bool read();
    bool write();

  protected:
    bool unpackSettings(File &file);
    void packSettings(File &file);
};

void Settings::reset()
{
    setup = true;
    sta = false;
    ssid = "";
    passphrase = "";
    ntp = "ntp.metas.ch";
}

void Settings::begin(const String &path)
{
    this->path = path;

    if (!read())
    {
      DBG_PRINTLN("SETTINGS: missing or invalid settings, fallback to default.");

      if (!write())
      {
        DBG_PRINTLN("SETTINGS: failed to write settings !");
      }
    }
}

const char UNPACKSETTINGS_INVALID_MAP_SIZE[] PROGMEM = "SETTINGS: invalid map size res=%i,size=%i\r\n";
const char UNPACKSETTINGS_INVALID_KEY[] PROGMEM = "SETTINGS: read key failed res=%i,size=%i\r\n";

bool Settings::unpackSettings(File &file)
{
  const size_t mapSize = 4;
  const size_t strSize = 64;
  char str[strSize];
  size_t size;
  bool res = msgpck_map_next(&file);
  if (!res)
    return false;
  
  res = msgpck_read_map_size(&file, &size);
  if (!res || size != mapSize)
  {
    DBG_PRINTF(UNPACKSETTINGS_INVALID_MAP_SIZE, res, size)
    return false;
  }

  for (size_t i = 0; i < mapSize; i++)
  {
    res = msgpck_read_string(&file, str, strSize, &size);
    if (!res)
    {
      DBG_PRINTF(UNPACKSETTINGS_INVALID_KEY, res, size)
      return false;
    }
    if (strncmp("setup", str, size) == 0)
    {
      res = msgpck_read_bool(&file, &setup);
    }
    else if (strncmp("sta", str, size) == 0)
    {
      res = msgpck_read_bool(&file, &sta);
    }
    else if (strncmp("ssid", str, size) == 0)
    {
      res = msgpck_read_string(&file, str, strSize, &size);
      DBG_PRINTF("k=%s,s=%d\r\n", str, size);
      if (res && size > 0 && size < 32)
      {
          ssid = String(str);
      }
      else
      { 
        DBG_PRINTF("SETTINGS: invalid ssid res=%i,size=%i,str=%s\r\n", res, size, str)
        res = false;
      }
    }
    else if (strncmp("passphrase", str, size) == 0)
    {
      res = msgpck_read_string(&file, str, strSize, &size);
      DBG_PRINTF("k=%s,s=%d\r\n", str, size);
      if (res && size > 7 && size < 64)
      {
          passphrase = String(str);
      }
      else
      { 
        DBG_PRINTF("SETTINGS: invalid passphrase res=%i,size=%i,str=%s\r\n", res, size, str)
        res = false;
      }
    }
    else
    {
      DBG_PRINTF("SETTINGS: unknown key res=%i,size=%i,str=%s\r\n", res, size, str)
      res = false;
    }

    if (!res)
      return false;    
  }

  return res;
}

bool Settings::read()
{
  reset();

  File file = SPIFFS.open(path, "r");
  if (!file)
  {
    DBG_PRINTF("SETTINGS: failed to open file\r\n")
    return false;
  }
  
  bool res = unpackSettings(file);
  file.close();
  return res;
}

void Settings::packSettings(File &file)
{
  DBG_PRINTLN("SETTINGS: write header size")
  msgpck_write_map_header(&file, 4);
  DBG_PRINTLN("SETTINGS: write setup")
  msgpck_write_string(&file, "setup");
  DBG_PRINTLN("SETTINGS: write setup value")
  msgpck_write_bool(&file, setup);
  DBG_PRINTLN("SETTINGS: write sta")
  msgpck_write_string(&file, "sta");
  DBG_PRINTLN("SETTINGS: write sta value")
  msgpck_write_bool(&file, sta);
  DBG_PRINTLN("SETTINGS: write ssid")
  msgpck_write_string(&file, "ssid");
  DBG_PRINTLN("SETTINGS: write ssid value " + String(ssid.length()))
  msgpck_write_string(&file, ssid);
  DBG_PRINTLN("SETTINGS: write passphrase")
  msgpck_write_string(&file, "passphrase");
  DBG_PRINTLN("SETTINGS: write passphrase value " + String(passphrase.length()))
  msgpck_write_string(&file, passphrase);
  file.flush();
  DBG_PRINTLN(file.size());
}

bool Settings::write()
{
  File file = SPIFFS.open(path, "w");
  if (!file)
  {
    DBG_PRINTF("SETTINGS: failed to open file\r\n")
    return false;
  }
  
  packSettings(file);
  file.close();
  return true;
}

#endif /* __SETTINGS_HPP__ */