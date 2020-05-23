#ifndef __AM2320DEVICE_HPP__
#define __AM2320DEVICE_HPP__

#include "Device.hpp"

#include "sensors/Sensors.hpp"

#include <Wire.h>
#include <Adafruit_AM2320.h>
#include <Adafruit_Sensor.h>

class Am2320Device : public Device
{
    public:
        void begin();
        Am2320Device() : _device(nullptr) {}
        ~Am2320Device() { if (_device != nullptr) { delete _device; _device = nullptr; }}
        virtual bool update();
        inline float humidity() const { return _humidity; }
        inline float temperature() const { return _temperature; }

    protected:
        Adafruit_AM2320 *_device;
        float _humidity;
        float _temperature;
};

void Am2320Device::begin() {
    _device = new Adafruit_AM2320();
    _device->begin();
}

bool Am2320Device::update() {
    _humidity = _device->readHumidity();
    _temperature = _device->readTemperature();
    return !isnan(_humidity) && !isnan(_temperature);
}

#endif // __AM2320DEVICE_HPP__