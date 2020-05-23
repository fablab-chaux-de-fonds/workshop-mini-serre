#ifndef __PULLUPDEVICE_HPP__
#define __PULLUPDEVICE_HPP__

#include <Arduino.h>
#include <c_types.h>

class PullUpDevice {
    public:
        void begin(u8 pin, u8 delay);
        bool isPulledDown(u64 duration);
        virtual bool update();

    private:
        u8 _delay;
        u64 _lastChange;
        bool _state;
        u8 _pin;
};

void PullUpDevice::begin(u8 pin, u8 delay) {
    _pin = pin;
    pinMode(_pin, INPUT);
    _delay = delay;
    _lastChange = millis();
    _state = digitalRead(_pin) == LOW;    
}

bool PullUpDevice::isPulledDown(u64 duration) {
    if (duration == 0) {
        return _state;
    }

    if (_state && millis() - _lastChange >= duration) {
        return true;
    }

    return false;
}

bool PullUpDevice::update() {
    bool newState = digitalRead(_pin) == LOW;
    bool hasChanged = newState != _state;
    if (!hasChanged) {
        return true;
    }

    u64 now = millis();
    if ((now - _lastChange) > (u16)_delay) {
        _state = newState;
    }

    if (hasChanged) {
        _lastChange = now;
    }

    return true;
}

#endif // __PULLUPDEVICE_HPP__
