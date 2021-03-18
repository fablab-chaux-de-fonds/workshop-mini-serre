// --

#include <Esp.h>
// #include <Wire.h>
// #include <Adafruit_AM2320.h>
// #include <Adafruit_Sensor.h>

#include "Settings.hpp"
#include "Manager.hpp"
#include "DataManager.hpp"

#include <CronTimers.h>



struct Sensors {
    TemperatureSensor airTemperature;
    HumiditySensor airHumidity;
    LightSensor lightIntensity;
    SoilSensor soilHumidity;
    BasicSensor<int> muliplexerDebug[16];
};

struct Managers {
    AirManager air;
    SoilManager soil;
    LightManager light;
    HourOfDayDataManager hourOfDayLog;
    DayOfWeekDataManager dayOfWeekLog;
    WeekOfYearDataManager weekOfYearLog;
    QuarterOfYearDataManager quarterOfYearLog;
    ButtonManager btn;
};

struct Hardware {
    // Inputs
    Am2320Device am2320;
    AnalogMultiplexerDevice<16> amux;
    PullUpDevice btn;

    // Outputs
    FanActuator fan;
    WaterPumpActuator waterPump;
    LightActuator ledStrip;
    LedActuator boardLed;
};

Sensors sen;
Managers mgr;
Hardware hw;
Settings set;

u8 state = 0;
static void trigger(int arg)
{
    hw.am2320.update();
    hw.amux.update();

    sen.airHumidity.update(hw.am2320.humidity());
    sen.airTemperature.update(hw.am2320.temperature());
    sen.lightIntensity.update(hw.amux.get(set.lightSensorIndex));
    sen.soilHumidity.update(hw.amux.get(1));

    mgr.air.update();

    if (state) {
        state = 0;
        hw.waterPump.set(0);
        hw.ledStrip.set(0);
    }
    else
    {
        state = 1;
        hw.waterPump.set(PWMRANGE);
        hw.ledStrip.set(PWMRANGE);
    }

    hw.waterPump.update();
    hw.ledStrip.update();
}

static const CronTimer crontab[] {
    // second,minute,hour,weekday,day/week#,month,year
    { "*/5 * * * * * *", trigger, 1 }
};

void setup() {
    Serial.begin(9600);
    
    Serial.println(" ~ Setup light sensor");
    sen.lightIntensity.begin(Board::LdrCurrentLimiter, Board::VccVoltage, 1024);

    // Setup AM2320 i2c device and link with sensors.
    Serial.println(" ~ Setup am2320 device");
    hw.am2320.begin(sen.airTemperature, sen.airHumidity);

    // Setup analog multiplexed values and link to sensors.
    Serial.println(" ~ Setup analog multiplexer device");
    hw.amux.begin(Board::SEL, Board::MM, Board::VccVoltage / 1024.0f);
     
    // Setup PWM ouputs
    Serial.println(" ~ Setup PWM devices");
    Serial.println(" - Air fan");
    hw.fan.begin(Board::FAN, 0, PWMRANGE);
    Serial.println(" - Water pump");
    hw.waterPump.begin(Board::WP, 0, PWMRANGE);
    Serial.println(" - Light strip");
    hw.ledStrip.begin(Board::LED, 0, PWMRANGE);

    // Setup digital input
    Serial.println(" ~ Setup Digital input devices");
    hw.btn.begin(Board::BTN, 50 /* ms */);

    // Link sensors and actuators into managers
    Serial.println(" ~ Configure sensor managers");
    Serial.println(" - Air humidity and temperature sensors");
    mgr.air.begin(sen.airTemperature, sen.airHumidity, hw.fan);
    Serial.println(" - Soil humidity sensors");
    mgr.soil.begin(sen.soilHumidity, hw.waterPump);
    Serial.println(" - Light intensity sensors");
    mgr.light.begin(sen.lightIntensity, hw.ledStrip);

    // Serial.println(" ~ Configure data loggers");
    mgr.hourOfDayLog.begin("hourOfDay");
    mgr.dayOfWeekLog.begin("dayOfWeek");
    mgr.weekOfYearLog.begin("weekOfYear");
    mgr.quarterOfYearLog.begin("quarterOfYear"); 
    // // , sen.airHumidity, sen.soilHumidity, sen.lightIntensity, hw.fan, hw.waterPump, hw.ledStrip
    
    Serial.println(" ~ Configure build-in LED manager");
    mgr.btn.begin(hw.btn, hw.boardLed);
}

u8 state = 0;

void loop() {

    static time_t   lastTime;
    time_t currentTime = time(NULL);
    if(currentTime != lastTime) {
        lastTime = currentTime;

#if 1
        struct tm tm;
        localtime_r(&currentTime, &tm);
        Serial.printf("local: %s", asctime(&tm));
#endif
        cronTimersTriggerAtTime(currentTime, crontab, sizeof(crontab)/sizeof(crontab[0]));
    }


    // Serial.println(sen.lightIntensity.value());
    // Serial.println(sen.soilHumidity.value());
    // Serial.println(sen.airHumidity.value());
    // Serial.println(sen.airTemperature.value());

    // // float a = am->readHumidity();
    // // float b = am->readTemperature();
    // // Serial.println(!isnan(a) && !isnan(b));
    // // Serial.println(a);
    // // Serial.println(b);

    // Serial.println(ESP.getFreeHeap());

    // // for (u8 i = 0; i < 16; i++) {
    // //     Serial.print(i);
    // //     Serial.print(" => ");
    // //     Serial.println(sen.muliplexerDebug[i].value());
    // // }
    // // Serial.println("--");
    // // Serial.println(analogRead(A0));
    
    // Serial.println("--");
    

    // delay(1000);


    // char v;
    // if (Serial.readBytes(&v, 1) == 0)
    // {
    //     return;
    // }

    // if (v == 'h') {
    //     Serial.println("High");
    //     high();
    // } else if (v == 'l') {
    //     Serial.println("Low");
    //     low();
    // } else if (v == 'o') {
    //     Serial.println("Open drain");
    //     open();
    // } else if (v == 'g') {
    //     Serial.println("Short to ground");
    //     ground();
    // } else if (v == 'r') {
    //     Serial.println("Read");
    //     Serial.println(read());
    // } else if (v == 'w') {
    //     Serial.println("Write");
    //     write();
    // } else if (v == 'n') {
    //     Serial.println(next());    
    // } else if (v == 's') {
    //     high();
    //     for (size_t i = 0; i < 16; i++) {
    //         if (next()) {
    //             Serial.print(i);
    //             Serial.print(" <= ");
    //             Serial.println("OK");
    //             if (i != 15) {
    //                 while (Serial.readBytes(&v, 1) != 0) {
    //                     delay(1);
    //                 }
    //             }
    //             break;
    //         } 
    //     }
    // } else if (v == 'p') {
    //     for (size_t j = 1; j <= 100; j++) {
    //         for (size_t i = 0; i < 16; i++) {
    //             next();
    //         }
    //     }
    //     for (size_t i = 0; i < 16; i++) {
    //         if (i == 5 || i == 10) {
    //             delay(1000);
    //         }
    //         next();
    //     }
    // } else {
    //     Serial.println("?");
    // }

    // // Ask devices to update their values
    // pinMode(D8, OUTPUT_OPEN_DRAIN);
    // delay(50);
    // pinMode(D8, INPUT_PULLDOWN_16);
    // delay(50);
    // u8 rco = digitalRead(D8);
    // Serial.println(rco);
    // delay(50);p
    // pinMode(D8, OUTPUT);
    // delay(50);

    // digitalWrite(D8, LOW);
    // Serial.println("LOW");
    // pinMode(D8, INPUT_PULLDOWN_16);
    // if (Serial.readString().length() > 0) {
    //     while(Serial.readString().length() <= 0) {
    //         Serial.println(digitalRead(D8));
    //     }
    // }
    // pinMode(D8, OUTPUT);
    // digitalWrite(D8, HIGH);
    // Serial.println("HIGH");
    // delay(100);

    // hw.am2320.update();
    // hw.amux.update();
    // hw.btn.update();

    // // Manager state updates
    // mgr.air.update();
    // mgr.soil.update();
    // mgr.light.update();
    // mgr.hourOfDayLog.update();
    // mgr.dayOfWeekLog.update();
    // mgr.weekOfYearLog.update();
    // mgr.quarterOfYearLog.update();
    // mgr.btn.update();

    // // Propagate value to devices
    // hw.fan.update();
    // hw.waterPump.update();
    // hw.ledStrip.update();
}


// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiAP.h>
// #include <ESP8266mDNS.h>

// // #include "DHTesp.h"

// #include <Adafruit_AM2320.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>

// #include <msgpck.h>

// #include <FS.h>

// // #include <Thing.h>
// #include <ESPAsyncTCP.h>
// // #include <WebThingAdapter.h>
// #include <ESPAsyncWebServer.h>

// #include "Settings.hpp"

// #define DBG Serial /**< Define where debug output will be printed. */

// #include "Actuator.hpp"
// #include "AnalogSensorManager.hpp"

// enum SensorState : u8
// {
//   Nominal,
//   TooHigh,
//   TooLow
// };

// template <typename TData, typename TActuator>
// class Sensor
// {
//   public:
//     TData value;
//     TData highThreshold;
//     TData lowThreshold;
//     u16 actuatorActivityDuration;
//     u16 actuatorDelayDuration;
//     u64 lastStateChanged;
//     SensorState state;
//     Actuator<TActuator> *actuator;
//     void deserialize(Stream *stream);
//     void serialize(Print *stream);
//     void update();
//     virtual TData read() = 0;
// };

// template <typename TData, typename TActuator>
// void Sensor<TData, TActuator>::update()
// {
//   value = read();

//   SensorState oldState = state;
//   if (value > highThreshold) {
//     state = TooHigh;
//   } else if (value < lowThreshold) {
//     state = TooLow;
//   } else {
//     state = Nominal;
//   }

//   if (state != oldState) {
//     lastStateChanged = millis();
//   }
  
//   switch (state)
//   {
//     case Nominal:
//       actuator.update()
//   };
  
// }

// class SoilSensor : public Sensor<float, u8> {
//   public:
//     void begin(int *rawValuePtr);
//     virtual float read();
//   private:
//     int *_rawValuePtr;
// };

// float SoilSensor::read() {
//   return 2.718282f * 2.718282f * (0.008985f * (*_rawValuePtr) + 0.207762f);
// }

// class AirHumiditySensor : public Sensor<float, u8> {
//   public:
//     void begin(Adafruit_AM2320 &sensor);
//     virtual float read();
//   private:
//     Adafruit_AM2320 &_sensor;
// };

// class AirTemperatureSensor : public Sensor<float, u8> {
//   public:
//     void begin(Adafruit_AM2320 &sensor);
//     virtual float read();
//   private:
//     Adafruit_AM2320 &_sensor;
// };

// float AirTemperatureSensor::read()
// {
//   return _sensor.readTemperature();
// }

// class LightSensor : public Sensor<float, bool> {

// };


// #define NBR_ANALOG_PINS 16

// // Physical properties
// int rawAnalogValues[NBR_ANALOG_PINS];
// AnalogSensorManager manager;

// //
// SoilSensor *soilSensors;
// LightSensor *lightSensors;
// AirTemperatureSensor *airTemperatureSensors;
// AirHumiditySensor *airHumiditySensor;

// Fan *fanActuators;
// Light *ligthActuators;
// WaterPump *pumpActuators;






// /* Setup debug printing macros. */
// #ifdef DBG
//   #define DBG_PRINT(...) { DBG.print(__VA_ARGS__); }
//   #define DBG_PRINTF(...) { DBG.printf(__VA_ARGS__); }
//   #define DBG_PRINTLN(...) { DBG.println(__VA_ARGS__); }
// #else
//   #define DBG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
//   #define DBG_PRINTF(...) {}
//   #define DBG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
// #endif
// //2.718282 * 2.718282 * (.008985 * moistVal * 1024 + 0.207762)
// // class DataRequestHandler : public RequestHandler
// // {
// //   public:
// //     virtual bool canHandle(HTTPMethod method, String uri) {
// //       return method == HTTPMethod::HTTP_GET && uri == "/csv";
// //     }
// //     virtual bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
// //       if (!server.hasArg("page"))
// //       {
// //         server.send(400, "text/plain", "error: missing page !");
// //         return true;
// //       }
// //       long page = server.arg("page").toInt();
// //       if (page <= 0)
// //       {
// //         server.send(400, "text/plain", "error: invalid page !");
// //         return false;
// //       }
// //       String fileName("/env/");
// //       fileName.concat(page - 1);
// //       if (SPIFFS.exists(fileName))
// //       {
// //         File file = SPIFFS.open(fileName, "r");
// //         if (!file)
// //         { 
// //           String msg("error: fail to read file ");
// //           msg.concat(fileName);
// //           server.send(500, "text/plain", msg);
// //         }
// //         else
// //         {
// //           server.streamFile(file, "text/csv");
// //           file.close();
// //         }
// //       }
// //       else
// //       {
// //         String msg("error: file not found ");
// //         msg.concat(fileName);
// //         server.send(404, "text/plain", msg);
// //       }
// //       return true;
// //     }
// // };


// // DataRequestHandler csvHandler;

// TwoWire i2c;

// DHT dht11(D5, DHT11);
// DHT dht22(D6, DHT22);
// Adafruit_AM2320 am2320(&i2c);

// MDNSResponder mdns;
// AsyncWebServer server(80);

// Settings settings;

// // WebThingAdapter *adapter;

// // const char *thingTypes[] = {"MultiLevelSwitch", "TemperatureSensor", nullptr};
// // ThingDevice thing("flcdf-ms", "Mini-Serre", thingTypes);
// // ThingProperty propMoisture("moist1", "Soil moisture sensor", NUMBER, "LevelProperty");
// // ThingProperty propTempDHT11("tempdht11", "DHT11 temperature", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityDHT11("hum_dht11", "DHT11 humidity", NUMBER, "LevelProperty");
// // ThingProperty propTempDHT22("temp_dht22", "DHt22 temperature", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityDHT22("hum_dht11", "DHT22 humidity", NUMBER, "LevelProperty");
// // ThingProperty propTempAM2320("temp_am2320", "am23", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityAM2320("hum_am2320", "", NUMBER, "LevelProperty");

// const char INDEX[] PROGMEM = R"=====(<!DOCTYPE HTML>
// <html>
// <head>
// <meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
// <title>ESP8266 Web Form Demo</title>
// <style>
// body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }
// </style>
// </head>
// <body>
// <h1>ESP8266 Web Form Demo</h1>
// <FORM action="/" method="post">
// <P>
// LED<br>
// <INPUT type="radio" name="LED" value="1">On<BR>
// <INPUT type="radio" name="LED" value="0">Off<BR>
// <INPUT type="submit" value="Send"> <INPUT type="reset">
// </P>
// </FORM>
// </body>
// </html>
// ")=====";

// void setupSerial()
// {
//   Serial.begin(9600);
//   Serial.println();
//   Serial.println("FabLab | La Chaux-de-Fonds");
//   Serial.println("ESP12E mini-serre controller");
// }

// const char msgWifiApStartFailed[] PROGMEM = "WIFI: Fail to start acess-point !";
// const char msgWifiApSetupFailed[] PROGMEM = "WIFI: Fail to setup access-point network !";
// const char msgWifiApMDnsFailed[] PROGMEM = "WIFI: Fail to setup DNS responder !";

// void setupWifiAp()
// {  
//   WiFi.persistent(false);
//   WiFi.setAutoConnect(false);
//   WiFi.setAutoReconnect(false);
//   WiFi.begin();
//   delay(100);
  
//   String mac(WiFi.macAddress());
//   Serial.println("WIFI: Device MAC is " + mac);
//   String sn(mac.substring(12, 14) + mac.substring(15, 17));
//   String ssid = "Mini-Serre (" + sn + ")";
//   String psk = "FL/MS-" + sn;
//   Serial.println("WIFI: SSID is " + ssid);
//   Serial.println("WIFI: PASSPHRASE is " + psk);
//   delay(100);
//   if (!WiFi.softAP(ssid.c_str(), psk.c_str()))
//   {
//     DBG_PRINTLN(msgWifiApStartFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: Started.");
//   delay(100);
//   IPAddress ip(192, 168, 33, 1);
//   IPAddress network(255, 255, 255, 0);
  
//   if (!WiFi.softAPConfig(ip, ip, network))
//   {
//     DBG_PRINTLN(msgWifiApSetupFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: Network setup completed.");
//   delay(100);
//   String host("ms" + sn + ".local");
//   host.toLowerCase();
//   if (!mdns.begin(host.c_str(), WiFi.localIP()))
//   {
//     DBG_PRINTLN(msgWifiApMDnsFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: mDns setup completed.");
// }

// void httpHandleRoot(AsyncWebServerRequest *request)
// {
//   request->send_P(200, "text/html", INDEX);
// }

// void httpHandleSetup(AsyncWebServerRequest *request)
// {
//   WebRequestMethodComposite method = request->method();

//   if (method == HTTP_GET)
//   {
//     if (!SPIFFS.exists(settings.path))
//     {
//       request->send(500, "text/plain", "invalid config");
//       return;
//     }

//     File file = SPIFFS.open(settings.path, "r");
//     if (!file)
//     {
//       request->send(500, "text/plain", "file config cannot be opened");
//       return;
//     }

//     AsyncResponseStream *stream = request->beginResponseStream("application/json");
//     msgpck_to_json(stream, &file);
//     file.close();
//     stream->setCode(200);
//     request->send(stream);
//   }
//   else if (method == HTTP_POST)
//   {
//     if (!request->hasArg("sta"))
//     {
//       request->send(400, "text/plain", "missing sta flag");
//       return;
//     }
//     if (!request->hasArg("ssid"))
//     {
//       request->send(400, "text/plain", "missing ssid");
//       return;
//     }
//     if (!request->hasArg("passphrase"))
//     {
//       request->send(400, "text/plain", "missing passphrase");
//       return;
//     }
//     settings.reset();
//     settings.sta = request->arg("sta").toInt() != 0;
//     settings.ssid.concat(request->arg("ssid"));
//     settings.passphrase.concat(request->arg("passphrase"));
//     settings.setup = false;
//     if (!settings.write())
//     {
//       request->send(400, "text/plain", "cannot be stored");
//       return;
//     }

//     settings.read();

//     request->send(200, "text/plain", "OK");
//   }
  
// }

// void setupHttpServer()
// {
//   server.begin();
//   server.on("/", httpHandleRoot);
//   server.on("/setup", httpHandleSetup);
//   // server.addHandler(&csvHandler);
// }

// unsigned long buttonPressedStart = millis();

// void ICACHE_RAM_ATTR OnButtonChanged()
// {
//   if (digitalRead(D7) == LOW)
//   {
//     buttonPressedStart = millis();
//     digitalWrite(LED_BUILTIN, LOW);
//   }
//   else
//   {
//     unsigned long delay = (millis() - buttonPressedStart);
//     digitalWrite(LED_BUILTIN, HIGH);
//     if (delay > 10000 && SPIFFS.exists("/cfg"))
//     {
//       SPIFFS.remove("/cfg");
//     }
    
//     if (delay > 50)
//     {
//       ESP.reset();
//     }
//   }
  
// }

// bool setupWifiClient()
// {
//   WiFi.persistent(true);
//   WiFi.setAutoConnect(true);
//   WiFi.setAutoReconnect(true);
//   if (!WiFi.begin(settings.ssid.c_str(), settings.passphrase.c_str()))
//   {
//     DBG_PRINTF("WIFIC: Failed to begin with %s, %s", settings.ssid.c_str(), settings.passphrase.c_str());
//     return false;
//   }

//   // Wait for connection
//   bool blink = true;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//     digitalWrite(LED_BUILTIN, blink ? LOW : HIGH); // active low led
//     blink = !blink;
//   }
//   digitalWrite(LED_BUILTIN, HIGH); // active low led

//   Serial.println("");
//   Serial.print("Connected to ");
//   Serial.println(settings.ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//   // adapter = new WebThingAdapter("w25", WiFi.localIP());

//   // thing.addProperty(&propMoisture);
//   // thing.addProperty(&propTempDHT11);
//   // thing.addProperty(&propHumidityDHT11);
//   // thing.addProperty(&propTempDHT22);
//   // thing.addProperty(&propHumidityDHT22);
//   // thing.addProperty(&propTempAM2320);
//   // thing.addProperty(&propHumidityAM2320);
//   // adapter->addDevice(&thing);
//   // adapter->begin();
//   Serial.println("HTTP server started");
//   Serial.print("http://");
//   Serial.print(WiFi.localIP());
//   // Serial.print("/things/");
//   // Serial.println(thing.id);

//   return true;
// }

// void setup()
// {
//   setupSerial();

//   if (!SPIFFS.begin())
//   {
//     DBG_PRINTLN("SPIFFS: failed to initialize !\r\n");
//   }

//   settings.begin("/cfg");

//   if (settings.sta)
//   {
//     DBG_PRINTLN("WIFI: Client mode selected !");
//     setupWifiClient();
//   }
//   else
//   {
//     DBG_PRINTLN("WIFI: Access point mode selected !");
//     setupWifiAp();
//   }
  
//   setupHttpServer();

//   pinMode(D4, OUTPUT);
//   digitalWrite(D4, HIGH);
//   pinMode(D7, INPUT_PULLUP);
//   attachInterrupt(D7, OnButtonChanged, CHANGE);

//   pinMode(D0, OUTPUT);

//   i2c.begin(D2, D1);
//   dht11.begin(); // Connect DHT sensor to GPIO NodeMCU D5
//   dht22.begin(); // Connect DHT sensor to GPIO NodeMCU D6
//   am2320.begin(); // Connect i2c with GPIO NodeMCU D1+D2
// }

// unsigned long lastMeasure = millis();

// uint8_t state = 0;
// uint8_t val = 0;
// unsigned long lastPwm = millis();

// void loop()
// {
//   mdns.update();

//   // bool on = ledOn.getValue().boolean;
//   // digitalWrite(LED_BUILTIN, on ? LOW : HIGH); // active low led

//   unsigned long now = millis();
//   if (now - lastMeasure > 2000UL)
//   {
//     lastMeasure = now;
//     state = !state;

//     size_t maxFileSize = 1024; // 1kB
//     size_t maxFiles = 10;
//     File file;
//     File ctx = SPIFFS.open("/env", "r");
//     size_t count = 0;
//     if (ctx)
//     {
//       size_t read = ctx.read((uint8_t*)&count, sizeof(size_t));
//       Serial.printf("Readed meta bytes %i\r\n", read);
//       if (read != sizeof(size_t))
//       {
//         count = 0;
//       }
//       ctx.close();
      
//       Serial.printf("File index from meta is %i\r\n", count);

//       char fileName[20];
//       snprintf(fileName, sizeof(fileName), "/env/%i", count);
//       file = SPIFFS.open(fileName, "a");
//       if (file)
//       {
//         Serial.printf("File size is %i\r\n", file.size());
//         if (file.size() > maxFileSize)
//         {
//           file.close();
//           count = (count + 1) % maxFiles;
//           Serial.printf("New file index is %i\r\n", count);
//           snprintf(fileName, sizeof(fileName), "/env/%i", count);
//           file = SPIFFS.open(fileName, "w");
//           if (file)
//           {
//             const char * header = "°C (AM2320);°C (dht11);°Chi (dht11);°C (dht22);°Chi (dht22);%REL (AM2320);%REL (dht11);%REL (dht22)\r\n";
//             file.write((const uint8_t*) header, strlen(header));
//           }
//         }
//       }
      
//       ctx = SPIFFS.open("/env", "w");
//       if (ctx.write((uint8_t*)&count, sizeof(size_t)) != sizeof(size_t))
//       {
//         Serial.println("Write error on index !");
//       }
//       ctx.close();

//       size_t size = 100;
//       char buffer[size];
//       snprintf(
//         buffer, 
//         size,
//         "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\r\n",
//         am2320.readTemperature(),
//         dht11.readTemperature(),  
//         dht11.computeHeatIndex(false), 
//         dht22.readTemperature(), 
//         dht22.computeHeatIndex(false),
//         am2320.readHumidity(), 
//         dht11.readHumidity(), 
//         dht22.readHumidity()
//       );
//       file.write((const uint8_t *)&buffer, min(strlen(buffer), size));
//       file.close();
//       Serial.println(buffer);
//       Serial.println("-----");
//     }
      
//     // ThingDataValue value;
//     // value.number = 2.718282 * 2.718282 * (.008985 * analogRead(A0) + 0.207762);
//     // propMoisture.setValue(value);
//     // value.number = am2320.readTemperature();
//     // propTempAM2320.setValue(value);
//     // value.number = dht11.readTemperature();
//     // propTempDHT11.setValue(value);
//     // value.number = dht22.readTemperature(); 
//     // propTempDHT22.setValue(value);
//     // value.number = am2320.readHumidity();
//     // propHumidityAM2320.setValue(value);
//     // value.number = dht11.readHumidity();
//     // propHumidityDHT11.setValue(value);
//     // value.number = dht22.readHumidity();
//     // propHumidityDHT22.setValue(value);
//   }


//   unsigned long delay = now - lastPwm;
//   if (delay >= 2)
//     {
//     if (state)
//     {
//       if (val < 255) {
//         lastPwm = now;
//         val++;
//         analogWrite(D0, val);
//       }
//     }
//     else {
//       if (val > 0) {
//         lastPwm = now;
//         val--;
//         analogWrite(D0, val);
//       }
//     }
//   }


//   // adapter->update();
// }


// #include <Arduino.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiAP.h>
// #include <ESP8266mDNS.h>

// // #include "DHTesp.h"

// #include <Adafruit_AM2320.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>

// #include <msgpck.h>

// #include <FS.h>

// // #include <Thing.h>
// #include <ESPAsyncTCP.h>
// // #include <WebThingAdapter.h>
// #include <ESPAsyncWebServer.h>

// #include "Settings.hpp"

// #define DBG Serial /**< Define where debug output will be printed. */

// #include "Actuator.hpp"
// #include "AnalogSensorManager.hpp"

// enum SensorState : u8
// {
//   Nominal,
//   TooHigh,
//   TooLow
// };

// template <typename TData, typename TActuator>
// class Sensor
// {
//   public:
//     TData value;
//     TData highThreshold;
//     TData lowThreshold;
//     u16 actuatorActivityDuration;
//     u16 actuatorDelayDuration;
//     u64 lastStateChanged;
//     SensorState state;
//     Actuator<TActuator> *actuator;
//     void deserialize(Stream *stream);
//     void serialize(Print *stream);
//     void update();
//     virtual TData read() = 0;
// };

// template <typename TData, typename TActuator>
// void Sensor<TData, TActuator>::update()
// {
//   value = read();

//   SensorState oldState = state;
//   if (value > highThreshold) {
//     state = TooHigh;
//   } else if (value < lowThreshold) {
//     state = TooLow;
//   } else {
//     state = Nominal;
//   }

//   if (state != oldState) {
//     lastStateChanged = millis();
//   }
  
//   switch (state)
//   {
//     case Nominal:
//       actuator.update()
//   };
  
// }

// class SoilSensor : public Sensor<float, u8> {
//   public:
//     void begin(int *rawValuePtr);
//     virtual float read();
//   private:
//     int *_rawValuePtr;
// };

// float SoilSensor::read() {
//   return 2.718282f * 2.718282f * (0.008985f * (*_rawValuePtr) + 0.207762f);
// }

// class AirHumiditySensor : public Sensor<float, u8> {
//   public:
//     void begin(Adafruit_AM2320 &sensor);
//     virtual float read();
//   private:
//     Adafruit_AM2320 &_sensor;
// };

// class AirTemperatureSensor : public Sensor<float, u8> {
//   public:
//     void begin(Adafruit_AM2320 &sensor);
//     virtual float read();
//   private:
//     Adafruit_AM2320 &_sensor;
// };

// float AirTemperatureSensor::read()
// {
//   return _sensor.readTemperature();
// }

// class LightSensor : public Sensor<float, bool> {

// };


// #define NBR_ANALOG_PINS 16

// // Physical properties
// int rawAnalogValues[NBR_ANALOG_PINS];
// AnalogSensorManager manager;

// //
// SoilSensor *soilSensors;
// LightSensor *lightSensors;
// AirTemperatureSensor *airTemperatureSensors;
// AirHumiditySensor *airHumiditySensor;

// Fan *fanActuators;
// Light *ligthActuators;
// WaterPump *pumpActuators;






// /* Setup debug printing macros. */
// #ifdef DBG
//   #define DBG_PRINT(...) { DBG.print(__VA_ARGS__); }
//   #define DBG_PRINTF(...) { DBG.printf(__VA_ARGS__); }
//   #define DBG_PRINTLN(...) { DBG.println(__VA_ARGS__); }
// #else
//   #define DBG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
//   #define DBG_PRINTF(...) {}
//   #define DBG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
// #endif
// //2.718282 * 2.718282 * (.008985 * moistVal * 1024 + 0.207762)
// // class DataRequestHandler : public RequestHandler
// // {
// //   public:
// //     virtual bool canHandle(HTTPMethod method, String uri) {
// //       return method == HTTPMethod::HTTP_GET && uri == "/csv";
// //     }
// //     virtual bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
// //       if (!server.hasArg("page"))
// //       {
// //         server.send(400, "text/plain", "error: missing page !");
// //         return true;
// //       }
// //       long page = server.arg("page").toInt();
// //       if (page <= 0)
// //       {
// //         server.send(400, "text/plain", "error: invalid page !");
// //         return false;
// //       }
// //       String fileName("/env/");
// //       fileName.concat(page - 1);
// //       if (SPIFFS.exists(fileName))
// //       {
// //         File file = SPIFFS.open(fileName, "r");
// //         if (!file)
// //         { 
// //           String msg("error: fail to read file ");
// //           msg.concat(fileName);
// //           server.send(500, "text/plain", msg);
// //         }
// //         else
// //         {
// //           server.streamFile(file, "text/csv");
// //           file.close();
// //         }
// //       }
// //       else
// //       {
// //         String msg("error: file not found ");
// //         msg.concat(fileName);
// //         server.send(404, "text/plain", msg);
// //       }
// //       return true;
// //     }
// // };


// // DataRequestHandler csvHandler;

// TwoWire i2c;

// DHT dht11(D5, DHT11);
// DHT dht22(D6, DHT22);
// Adafruit_AM2320 am2320(&i2c);

// MDNSResponder mdns;
// AsyncWebServer server(80);

// Settings settings;

// // WebThingAdapter *adapter;

// // const char *thingTypes[] = {"MultiLevelSwitch", "TemperatureSensor", nullptr};
// // ThingDevice thing("flcdf-ms", "Mini-Serre", thingTypes);
// // ThingProperty propMoisture("moist1", "Soil moisture sensor", NUMBER, "LevelProperty");
// // ThingProperty propTempDHT11("tempdht11", "DHT11 temperature", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityDHT11("hum_dht11", "DHT11 humidity", NUMBER, "LevelProperty");
// // ThingProperty propTempDHT22("temp_dht22", "DHt22 temperature", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityDHT22("hum_dht11", "DHT22 humidity", NUMBER, "LevelProperty");
// // ThingProperty propTempAM2320("temp_am2320", "am23", NUMBER, "TemperatureProperty");
// // ThingProperty propHumidityAM2320("hum_am2320", "", NUMBER, "LevelProperty");

// const char INDEX[] PROGMEM = R"=====(<!DOCTYPE HTML>
// <html>
// <head>
// <meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
// <title>ESP8266 Web Form Demo</title>
// <style>
// body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }
// </style>
// </head>
// <body>
// <h1>ESP8266 Web Form Demo</h1>
// <FORM action="/" method="post">
// <P>
// LED<br>
// <INPUT type="radio" name="LED" value="1">On<BR>
// <INPUT type="radio" name="LED" value="0">Off<BR>
// <INPUT type="submit" value="Send"> <INPUT type="reset">
// </P>
// </FORM>
// </body>
// </html>
// ")=====";

// void setupSerial()
// {
//   Serial.begin(9600);
//   Serial.println();
//   Serial.println("FabLab | La Chaux-de-Fonds");
//   Serial.println("ESP12E mini-serre controller");
// }

// const char msgWifiApStartFailed[] PROGMEM = "WIFI: Fail to start acess-point !";
// const char msgWifiApSetupFailed[] PROGMEM = "WIFI: Fail to setup access-point network !";
// const char msgWifiApMDnsFailed[] PROGMEM = "WIFI: Fail to setup DNS responder !";

// void setupWifiAp()
// {  
//   WiFi.persistent(false);
//   WiFi.setAutoConnect(false);
//   WiFi.setAutoReconnect(false);
//   WiFi.begin();
//   delay(100);
  
//   String mac(WiFi.macAddress());
//   Serial.println("WIFI: Device MAC is " + mac);
//   String sn(mac.substring(12, 14) + mac.substring(15, 17));
//   String ssid = "Mini-Serre (" + sn + ")";
//   String psk = "FL/MS-" + sn;
//   Serial.println("WIFI: SSID is " + ssid);
//   Serial.println("WIFI: PASSPHRASE is " + psk);
//   delay(100);
//   if (!WiFi.softAP(ssid.c_str(), psk.c_str()))
//   {
//     DBG_PRINTLN(msgWifiApStartFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: Started.");
//   delay(100);
//   IPAddress ip(192, 168, 33, 1);
//   IPAddress network(255, 255, 255, 0);
  
//   if (!WiFi.softAPConfig(ip, ip, network))
//   {
//     DBG_PRINTLN(msgWifiApSetupFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: Network setup completed.");
//   delay(100);
//   String host("ms" + sn + ".local");
//   host.toLowerCase();
//   if (!mdns.begin(host.c_str(), WiFi.localIP()))
//   {
//     DBG_PRINTLN(msgWifiApMDnsFailed);
//     delay(100);
//     ESP.reset();
//   }
//   DBG_PRINTLN("WIFI: mDns setup completed.");
// }

// void httpHandleRoot(AsyncWebServerRequest *request)
// {
//   request->send_P(200, "text/html", INDEX);
// }

// void httpHandleSetup(AsyncWebServerRequest *request)
// {
//   WebRequestMethodComposite method = request->method();

//   if (method == HTTP_GET)
//   {
//     if (!SPIFFS.exists(settings.path))
//     {
//       request->send(500, "text/plain", "invalid config");
//       return;
//     }

//     File file = SPIFFS.open(settings.path, "r");
//     if (!file)
//     {
//       request->send(500, "text/plain", "file config cannot be opened");
//       return;
//     }

//     AsyncResponseStream *stream = request->beginResponseStream("application/json");
//     msgpck_to_json(stream, &file);
//     file.close();
//     stream->setCode(200);
//     request->send(stream);
//   }
//   else if (method == HTTP_POST)
//   {
//     if (!request->hasArg("sta"))
//     {
//       request->send(400, "text/plain", "missing sta flag");
//       return;
//     }
//     if (!request->hasArg("ssid"))
//     {
//       request->send(400, "text/plain", "missing ssid");
//       return;
//     }
//     if (!request->hasArg("passphrase"))
//     {
//       request->send(400, "text/plain", "missing passphrase");
//       return;
//     }
//     settings.reset();
//     settings.sta = request->arg("sta").toInt() != 0;
//     settings.ssid.concat(request->arg("ssid"));
//     settings.passphrase.concat(request->arg("passphrase"));
//     settings.setup = false;
//     if (!settings.write())
//     {
//       request->send(400, "text/plain", "cannot be stored");
//       return;
//     }

//     settings.read();

//     request->send(200, "text/plain", "OK");
//   }
  
// }

// void setupHttpServer()
// {
//   server.begin();
//   server.on("/", httpHandleRoot);
//   server.on("/setup", httpHandleSetup);
//   // server.addHandler(&csvHandler);
// }

// unsigned long buttonPressedStart = millis();

// void ICACHE_RAM_ATTR OnButtonChanged()
// {
//   if (digitalRead(D7) == LOW)
//   {
//     buttonPressedStart = millis();
//     digitalWrite(LED_BUILTIN, LOW);
//   }
//   else
//   {
//     unsigned long delay = (millis() - buttonPressedStart);
//     digitalWrite(LED_BUILTIN, HIGH);
//     if (delay > 10000 && SPIFFS.exists("/cfg"))
//     {
//       SPIFFS.remove("/cfg");
//     }
    
//     if (delay > 50)
//     {
//       ESP.reset();
//     }
//   }
  
// }

// bool setupWifiClient()
// {
//   WiFi.persistent(true);
//   WiFi.setAutoConnect(true);
//   WiFi.setAutoReconnect(true);
//   if (!WiFi.begin(settings.ssid.c_str(), settings.passphrase.c_str()))
//   {
//     DBG_PRINTF("WIFIC: Failed to begin with %s, %s", settings.ssid.c_str(), settings.passphrase.c_str());
//     return false;
//   }

//   // Wait for connection
//   bool blink = true;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//     digitalWrite(LED_BUILTIN, blink ? LOW : HIGH); // active low led
//     blink = !blink;
//   }
//   digitalWrite(LED_BUILTIN, HIGH); // active low led

//   Serial.println("");
//   Serial.print("Connected to ");
//   Serial.println(settings.ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//   // adapter = new WebThingAdapter("w25", WiFi.localIP());

//   // thing.addProperty(&propMoisture);
//   // thing.addProperty(&propTempDHT11);
//   // thing.addProperty(&propHumidityDHT11);
//   // thing.addProperty(&propTempDHT22);
//   // thing.addProperty(&propHumidityDHT22);
//   // thing.addProperty(&propTempAM2320);
//   // thing.addProperty(&propHumidityAM2320);
//   // adapter->addDevice(&thing);
//   // adapter->begin();
//   Serial.println("HTTP server started");
//   Serial.print("http://");
//   Serial.print(WiFi.localIP());
//   // Serial.print("/things/");
//   // Serial.println(thing.id);

//   return true;
// }

// void setup()
// {
//   setupSerial();

//   if (!SPIFFS.begin())
//   {
//     DBG_PRINTLN("SPIFFS: failed to initialize !\r\n");
//   }

//   settings.begin("/cfg");

//   if (settings.sta)
//   {
//     DBG_PRINTLN("WIFI: Client mode selected !");
//     setupWifiClient();
//   }
//   else
//   {
//     DBG_PRINTLN("WIFI: Access point mode selected !");
//     setupWifiAp();
//   }
  
//   setupHttpServer();

//   pinMode(D4, OUTPUT);
//   digitalWrite(D4, HIGH);
//   pinMode(D7, INPUT_PULLUP);
//   attachInterrupt(D7, OnButtonChanged, CHANGE);

//   pinMode(D0, OUTPUT);

//   i2c.begin(D2, D1);
//   dht11.begin(); // Connect DHT sensor to GPIO NodeMCU D5
//   dht22.begin(); // Connect DHT sensor to GPIO NodeMCU D6
//   am2320.begin(); // Connect i2c with GPIO NodeMCU D1+D2
// }

// unsigned long lastMeasure = millis();

// uint8_t state = 0;
// uint8_t val = 0;
// unsigned long lastPwm = millis();

// void loop()
// {
//   mdns.update();

//   // bool on = ledOn.getValue().boolean;
//   // digitalWrite(LED_BUILTIN, on ? LOW : HIGH); // active low led

//   unsigned long now = millis();
//   if (now - lastMeasure > 2000UL)
//   {
//     lastMeasure = now;
//     state = !state;

//     size_t maxFileSize = 1024; // 1kB
//     size_t maxFiles = 10;
//     File file;
//     File ctx = SPIFFS.open("/env", "r");
//     size_t count = 0;
//     if (ctx)
//     {
//       size_t read = ctx.read((uint8_t*)&count, sizeof(size_t));
//       Serial.printf("Readed meta bytes %i\r\n", read);
//       if (read != sizeof(size_t))
//       {
//         count = 0;
//       }
//       ctx.close();
      
//       Serial.printf("File index from meta is %i\r\n", count);

//       char fileName[20];
//       snprintf(fileName, sizeof(fileName), "/env/%i", count);
//       file = SPIFFS.open(fileName, "a");
//       if (file)
//       {
//         Serial.printf("File size is %i\r\n", file.size());
//         if (file.size() > maxFileSize)
//         {
//           file.close();
//           count = (count + 1) % maxFiles;
//           Serial.printf("New file index is %i\r\n", count);
//           snprintf(fileName, sizeof(fileName), "/env/%i", count);
//           file = SPIFFS.open(fileName, "w");
//           if (file)
//           {
//             const char * header = "°C (AM2320);°C (dht11);°Chi (dht11);°C (dht22);°Chi (dht22);%REL (AM2320);%REL (dht11);%REL (dht22)\r\n";
//             file.write((const uint8_t*) header, strlen(header));
//           }
//         }
//       }
      
//       ctx = SPIFFS.open("/env", "w");
//       if (ctx.write((uint8_t*)&count, sizeof(size_t)) != sizeof(size_t))
//       {
//         Serial.println("Write error on index !");
//       }
//       ctx.close();

//       size_t size = 100;
//       char buffer[size];
//       snprintf(
//         buffer, 
//         size,
//         "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\r\n",
//         am2320.readTemperature(),
//         dht11.readTemperature(),  
//         dht11.computeHeatIndex(false), 
//         dht22.readTemperature(), 
//         dht22.computeHeatIndex(false),
//         am2320.readHumidity(), 
//         dht11.readHumidity(), 
//         dht22.readHumidity()
//       );
//       file.write((const uint8_t *)&buffer, min(strlen(buffer), size));
//       file.close();
//       Serial.println(buffer);
//       Serial.println("-----");
//     }
      
//     // ThingDataValue value;
//     // value.number = 2.718282 * 2.718282 * (.008985 * analogRead(A0) + 0.207762);
//     // propMoisture.setValue(value);
//     // value.number = am2320.readTemperature();
//     // propTempAM2320.setValue(value);
//     // value.number = dht11.readTemperature();
//     // propTempDHT11.setValue(value);
//     // value.number = dht22.readTemperature(); 
//     // propTempDHT22.setValue(value);
//     // value.number = am2320.readHumidity();
//     // propHumidityAM2320.setValue(value);
//     // value.number = dht11.readHumidity();
//     // propHumidityDHT11.setValue(value);
//     // value.number = dht22.readHumidity();
//     // propHumidityDHT22.setValue(value);
//   }


//   unsigned long delay = now - lastPwm;
//   if (delay >= 2)
//     {
//     if (state)
//     {
//       if (val < 255) {
//         lastPwm = now;
//         val++;
//         analogWrite(D0, val);
//       }
//     }
//     else {
//       if (val > 0) {
//         lastPwm = now;
//         val--;
//         analogWrite(D0, val);
//       }
//     }
//   }


//   // adapter->update();
// }
