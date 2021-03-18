#ifndef __SOILSENSOR_HPP__
#define __SOILSENSOR_HPP__

#include "Sensors.hpp"

class SoilSensor : public Sensor<int, float> {
    public:
        virtual void update(int rawValue);
};

void SoilSensor::update(int rawValue) {
    _value = 2.718282f * 2.718282f * (0.008985f * rawValue + 0.207762f);
}

#endif // __SOILSENSOR_HPP__