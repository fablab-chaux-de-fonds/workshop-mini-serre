#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <Arduino.h>
#include <c_types.h>

#include "sensors/Sensors.hpp"
#include "sensors/LightSensor.hpp"
#include "sensors/SoilSensor.hpp"

#include "devices/PullUpDevice.hpp"
#include "devices/PwmDevice.hpp"
#include "devices/Am2320Device.hpp"
#include "devices/AnalogMultiplexerDevice.hpp"

#include <ESPDateTime.h>

struct Board {
  static const u16 PwmMaxValue = 1023;
  static const float VccVoltage; 
  static const float LdrCurrentLimiter; 
  static const int MM  = A0;
  static const int BTN = D0;
  static const int WP  = D5;
  static const int FAN = D6;
  static const int SEL = D7; 
  static const int LED = D8; 
};

const float Board::VccVoltage = 3.3f; // Volts
const float Board::LdrCurrentLimiter = 10.0f; // kOhm

// ESP8266 has 0-1023 pwm range and require a 16bit value field
typedef PwmDevice<u16> FanActuator;
typedef PwmDevice<u16> WaterPumpActuator;
typedef PwmDevice<u16> LightActuator;
typedef PwmDevice<u16> LedActuator;

/**
 * A manager is just an abstraction of 
 * something that require to be updated at each loop.
 */
class Manager {
    public:
        virtual void update() = 0;
};

class ThresholdManager : Manager {
    public:
        virtual void update();
    protected:
        virtual bool thresholdExceeded() = 0;
        virtual bool actuator(float value) = 0;
        bool _enabled;
        time_t _enabledFromUtc;
        time_t _enabledSinceUtc;
        u64 _actuatorStart;
        u64 _actuatorOnDuration;
        u64 _sleepBeforeNewAction;
};

void ThresholdManager::update() {
    if (!_enabled) {
        actuator(0);
        return;
    }

    time_t utcNow = DateTime.utcTime();
    if (utcNow < _enabledFromUtc || _enabledSinceUtc > utcNow) {
        actuator(0);
        return;
    }

    u64 now = millis();
    if (_actuatorStart != 0) {
        if (now - _actuatorStart > _actuatorOnDuration) {
            actuator(0);
            if (now - _actuatorStart > _sleepBeforeNewAction) {
                _actuatorStart = 0;
            }
        }
    } else if (thresholdExceeded()) {
        if (actuator(1)) {
            _actuatorStart = now;
        }
    }
}

class AirManager : public ThresholdManager
{
    public:
        void begin(TemperatureSensor& temperature, HumiditySensor& humidity, FanActuator &actuator);
        virtual bool thresholdExceeded();
        virtual bool actuator(float value);

    protected:
        TemperatureSensor *_temperature;
        HumiditySensor *_humidity;
        FanActuator *_actuator;
        float _temperatureThreshold;
        float _humidityThreshold;
};

void AirManager::begin(TemperatureSensor& temperature, HumiditySensor& humidity, FanActuator &actuator) {
    _temperature = &temperature;
    _humidity = &humidity;
    _actuator = &actuator;
}

bool AirManager::thresholdExceeded() {
    return _temperature->value() > _temperatureThreshold
        || _humidity->value() > _humidityThreshold;
}

bool AirManager::actuator(float value) {
    _actuator->set(map(value, 0.0f, 1.0f, 0.0f, 1023.0f));
    return true;
}

class SoilManager : public ThresholdManager
{
    public:
        void begin(SoilSensor &sensor, PwmDevice<u16> &actuator);
        virtual bool thresholdExceeded();
        virtual bool actuator(float value);

    protected:
        SoilSensor *_sensor;
        WaterPumpActuator *_actuator;
        float _humidityThreshold;
};

void SoilManager::begin(SoilSensor &sensor, PwmDevice<u16> &actuator) {
    _sensor = &sensor;
    _actuator = &actuator;
}

bool SoilManager::thresholdExceeded() {
    return _sensor->value() < _humidityThreshold;
}

bool SoilManager::actuator(float value) {
    _actuator->set(map(value, 0.0f, 1.0f, 0.0f, 1023.0f));
    return true;
}

class LightManager : public ThresholdManager
{
    public:
        void begin(LightSensor &sensor, PwmDevice<u16> &actuator);
        virtual bool thresholdExceeded();
        virtual bool actuator(float value);

    protected:
        LightSensor *_sensor;
        PwmDevice<u16> *_actuator;
        float _lightIntensityThreshold;
};

void LightManager::begin(LightSensor &sensor, PwmDevice<u16> &actuator) {
    _sensor = &sensor;
    _actuator = &actuator;
}

bool LightManager::thresholdExceeded() {
    return _sensor->value() < _lightIntensityThreshold;
}

bool LightManager::actuator(float value) {
    _actuator->set(map(value, 0.0f, 1.0f, 0.0f, 1023.0f));
    return true;
}


class ButtonManager : public Manager
{
    public:
        void begin(PullUpDevice &button, PwmDevice<u16> &builtInLed);
        virtual void update();

    protected:
        PullUpDevice *_button;
        PwmDevice<u16> *_builtInLed;
};

void ButtonManager::begin(PullUpDevice &button, PwmDevice<u16> &builtInLed) {
    _button = &button;
    _builtInLed = &builtInLed;
}

void ButtonManager::update() {
    if (_button->isPulledDown(0)) {
        if (_button->isPulledDown(10000)) {
            _builtInLed->set(1023);
        } else {
            _builtInLed->set(512);
        }
    } else {
        _builtInLed->set(0);
    }
}

#endif // __MANAGER_HPP__