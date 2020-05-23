#ifndef __SENSORS_HPP__
#define __SENSORS_HPP__

template <typename TValue>
class RawSensor {
    public:
        virtual void update(TValue rawValue) = 0;
};

template <typename TRawValue, typename TValue>
class Sensor : public RawSensor<TRawValue> {
    public:
        inline TValue value() { return _value; }
    protected:
        TValue _value;
};

template <typename TValue>
class BasicSensor : public Sensor<TValue, TValue> {
    public:
        virtual void update(TValue rawValue);
};

template <typename TValue>
void BasicSensor<TValue>::update(TValue value) {
    this->_value = value;
}

class TemperatureSensor : public BasicSensor<float> {};

class HumiditySensor : public BasicSensor<float> {};

#endif