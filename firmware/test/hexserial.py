# -*- coding: utf-8 -*-
import serial
print (serial.__version__)
#3.4
ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout = None
)

while 1:
    print hex(int(ser.read().encode('hex'), 16))