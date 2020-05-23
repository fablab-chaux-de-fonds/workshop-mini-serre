#ifndef __PWMDEVICE_HPP__
#define __PWMDEVICE_HPP__

#include "Device.hpp"

#include <Arduino.h>
#include <c_types.h>

template <typename TValue>
class PwmDevice : public Device {
    public:
        void begin(u8 pin, TValue minValue, TValue maxValue);
        virtual bool update();
        void set(TValue value);
        inline TValue value() { return _value; }
    protected:
        u8 _pin;
        TValue _value;
        TValue _minValue;
        TValue _maxValue;
};

template <typename TValue>
void PwmDevice<TValue>::begin(u8 pin, TValue minValue, TValue maxValue) {
    _pin = pin;
    _value = minValue;
    _minValue = minValue;
    _maxValue = maxValue;
    pinMode(pin, OUTPUT);
    update();
}

template <typename TValue>
void PwmDevice<TValue>::set(TValue value) {
    if (value < _minValue) {
        _value = 0;
    } else if (value > _maxValue) {
        _value = _maxValue;
    } else {
        _value = value;
    }
}

template <typename TValue>
bool PwmDevice<TValue>::update() {
    analogWrite(_pin, _value);
    return true;
}

#endif // __PWMDEVICE_HPP__