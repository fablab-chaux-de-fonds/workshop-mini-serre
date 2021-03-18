#ifndef __LIGHTSENSOR_HPP__
#define __LIGHTSENSOR_HPP__

#include "Sensors.hpp"

class LightSensor : public Sensor<int, float> {
    public:
        void begin(float ldrCurrentLimiter, float ldrVcc, int adcSteps);
        virtual void update(int rawValue);
    protected:
        float _ldrCurrentLimiter; // LDR current limiter resistor
        float _ldrVcc; // Potential before resistor
        int _adcSteps;
};

void LightSensor::begin(float ldrCurrentLimiter, float ldrVcc, int adcSteps) {
    _ldrCurrentLimiter = ldrCurrentLimiter;
    _ldrVcc = ldrVcc;
    _adcSteps = adcSteps;
}

void LightSensor::update(int rawValue) {
    // http://emant.com/316002.page
    _value = 500.0f / (_ldrCurrentLimiter * (_ldrVcc / (rawValue * _ldrVcc / _adcSteps) - 1.0f));
}

#endif // __LIGHTSENSOR_HPP__