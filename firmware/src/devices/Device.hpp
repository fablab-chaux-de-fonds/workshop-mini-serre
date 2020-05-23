#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

class Device {
    public:
        virtual bool update() = 0;
};

template <u8 N, typename T>
class ValueDevice {
    public:
        inline T get(u8 index) { return _values[index % N]; }

    protected:
        T _values[N];
};

#endif // __DEVICE_HPP__
