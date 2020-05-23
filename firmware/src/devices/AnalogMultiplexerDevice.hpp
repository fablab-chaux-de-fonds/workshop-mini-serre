#ifndef __ANALOGMULTIPLEXERDEVICE_HPP__
#define __ANALOGMULTIPLEXERDEVICE_HPP__

#include "Device.hpp"
#include "sensors/Sensors.hpp"

#include <c_types.h>

#include <Arduino.h>

/**
 * This is an abstraction of an counter and an multiplexer in 
 * order to use only two pins (digital and analog) to handle 
 * up to N values depending on counter and multiplexer characteristics.
 * 
 * Digital pin is used as in/out to select current multiplexer output pin.
 */
template <u8 N>
class AnalogMultiplexerDevice : public ValueDevice<N, float>
{
    public:
        void begin(u8 ctrlPin, u8 valuePin, float analogToVolt);
        virtual bool update();

    protected:
        u8 _ctrlPin;
        u8 _valuePin;
        float _analogToVolt;
        bool next();
};

template <u8 N>
void AnalogMultiplexerDevice<N>::begin(u8 ctrlPin, u8 valuePin, float analogToVolt) {
    _ctrlPin = ctrlPin;
    _valuePin = valuePin;
    _analogToVolt = analogToVolt;
}

template <u8 N>
bool AnalogMultiplexerDevice<N>::update() {
    bool rco = false;

    // Search the first position of the multiplexer.
    // this position is when the counter raising the RCO
    // flag on last position.
    for (u8 i = 0; i < N; i++) {
        rco = next();
        if (rco) {
            break;
        }
    } 

    // RCO should be found in a N
    // possible positions. Otherwise 
    // we cannot continue.
    if (!rco) {
        return false;
    }

    // We are not in the first position.
    // Proceeding to reading of all possible values and update 
    // related sensor.
    for (u8 i = 0; i < N; i++) {
        ValueDevice<N, float>::_values[i] = _analogToVolt * analogRead(_valuePin);
        next();
    }

    return true;
}

template <u8 N>
bool AnalogMultiplexerDevice<N>::next() {
    // First of all we need to read the RCO flag
    // because it is high on the next digit
    // and we want to know the zero position.
    pinMode(D7, INPUT);

    // Waiting stable mesurement
    delayMicroseconds(10);

    // RCO flag is the last position on the multiplexed device.
    bool rco = digitalRead(D7);
    if (rco) {
        // Because RCO flag is shared with
        // clock and RCO is high we need to pulldown
        // to move from last to first position.
        pinMode(D7, OUTPUT);
        digitalWrite(D7, LOW);
    } 
    else
    {
        // Switching from high impedence to normal output 
        // is the only way found to move until next position
        // without stepping over due to rising of RCO flag.
        pinMode(D7, OUTPUT_OPEN_DRAIN);
        pinMode(D7, OUTPUT);
    }

    // Waiting is required to avoid multiple steps in once.
    delayMicroseconds(10);

    // Counter is reacting on rising edge. 
    // At that point we really reach the next position.
    digitalWrite(D7, HIGH);
    return rco;
}

#endif // __ANALOGMULTIPLEXERDEVICE_HPP__