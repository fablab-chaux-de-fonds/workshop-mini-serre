#include <Arduino.h>

#define DBG Serial /**< Define where debug output will be printed. */
#define DBG_MGR DBG

#include <unity.h>
#include <FS.h>

#include <DateTime.h>
#include "DataManager.hpp"

HourOfDayDataManager manager;

std::function<bool ()> boolData = []() { return true; };
std::function<int ()> intData = []() { return 30; };
std::function<float ()> floatData = []() { return 42.0f; };
std::function<String ()> strData = []() { return "Hello world !"; };

// class StringPrint : Print {
//     public:
//         virtual size_t write(byte value) {

//         }
//         char buffer[1024];
// }

#define BASETIME 1574870400

void test_update_1()
{
    // All updates in same minute should not update logs except first one
    for (size_t i = 1; i < 60; i+=2) {
        DateTime.setTime(BASETIME + i, true);
        manager.update();
    }   

    File f = SPIFFS.open("/tmp16", "r");
    f.setTimeCallback(&utcTime);
    msgpck_to_json(&Serial, &f);
    TEST_ASSERT_EQUAL(16, manager.getLastFileIndex());
    TEST_ASSERT_EQUAL(BASETIME + 1, manager.getLastUpdate());
    TEST_ASSERT_NOT_EQUAL(false, f);
    TEST_ASSERT_EQUAL(133, f.size());
    f.close();

    // All updates in same minute should not update logs except first one
    for (size_t i = 60; i < 120; i+=2) {
        DateTime.setTime(BASETIME + i, true);
        manager.update();
    }

    f = SPIFFS.open("/tmp16", "r");
    f.setTimeCallback(&utcTime);
    msgpck_to_json(&Serial, &f);
    TEST_ASSERT_EQUAL(16, manager.getLastFileIndex());
    TEST_ASSERT_EQUAL(BASETIME + 1, manager.getLastUpdate());
    TEST_ASSERT_NOT_EQUAL(false, f);
    TEST_ASSERT_EQUAL(133, f.size());
    f.close();
}

void test_update_2()
{
    // All updates in same minute should not update logs except first one
    // should move to next file because it is hour of day tests
    for (size_t i = 3601; i < 3660; i++) {
        DateTime.setTime(BASETIME + i, true);
        manager.update();
    }

    File f = SPIFFS.open("/tmp17", "r");
    msgpck_to_json(&Serial, &f);
    TEST_ASSERT_NOT_EQUAL(false, f);
    TEST_ASSERT_EQUAL(133, f.size());
    f.close();
}

void setup() {
    delay(2000);
    timeval tv;
    tv.tv_sec = BASETIME;
    tv.tv_usec = 0;
    timezone tz;
    tz.tz_dsttime = 0;
    tz.tz_minuteswest = 0;
    settimeofday(&tv, &tz);
    
    for (size_t i = 0; i < 23; i++) {
        String fileName("/tmp" + i);
        if (SPIFFS.exists(fileName)) {
            SPIFFS.remove(fileName);
        }
    }

    manager.begin("/tmp");
    manager.add<bool>("bool", boolData);
    manager.add<int>("int", intData);
    manager.add<float>("float", floatData);
    manager.add<String>("string", strData);
    
    UNITY_BEGIN();
    
    SPIFFS.begin();

    DateTime += BASETIME + 1;

    RUN_TEST(test_update_1);
    RUN_TEST(test_update_2);

    UNITY_END();
}

void loop() {
    


    // byte data[63] { }

    // for (size_t i = 0; i < 2; i++) {
    //     File f = SPIFFS.open("/tmp" + i, "a+");
    //     TEST_ASSERT_NOT_EQUAL(f, false);
    //     OUTPUT
    //     msgpck_to_json(&Serial, &f);
    //     f.close();
    // }


    // // TEST_ASSERT_EQUAL(File::exists("/tmp0"), true);
    // // TEST_ASSERT_EQUAL(File::exists("/tmp1"), true);
    // // UNITY_TEST_ASSERT(!File__exists("/tmp0"), 1, "original file hour zero not found");

    // UNITY_END(); // stop unit testing
}