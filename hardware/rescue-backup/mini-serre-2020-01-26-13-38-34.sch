EESchema Schematic File Version 2
LIBS:ESP8266
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mini-serre-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Mini-Serre"
Date "2020-01-26"
Rev "R01"
Comp "FabLab | La Chaux-de-Fonds"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP-12F U1
U 1 1 5E2D5255
P 5550 2750
F 0 "U1" H 5550 2650 50  0000 C CNN
F 1 "ESP-12F" H 5550 2850 50  0000 C CNN
F 2 "ESP:ESP-12E_SMD" H 5550 2750 50  0001 C CNN
F 3 "" H 5550 2750 50  0001 C CNN
	1    5550 2750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P1
U 1 1 5E2D5331
P 7250 2550
F 0 "P1" H 7250 2750 50  0000 C CNN
F 1 "CONN_01X03" V 7350 2550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03" H 7250 2550 50  0001 C CNN
F 3 "" H 7250 2550 50  0000 C CNN
	1    7250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2450 7050 2450
Wire Wire Line
	6450 2550 7050 2550
Text GLabel 7050 2850 3    60   Input ~ 0
GND
Wire Wire Line
	7050 2850 7050 2650
Text GLabel 4650 3350 3    60   Input ~ 0
3V3
Wire Wire Line
	4650 3350 4650 3150
Text GLabel 6450 3300 3    60   Input ~ 0
GND
Wire Wire Line
	6450 3150 6450 3300
$Comp
L CONN_01X03 P?
U 1 1 5E2D54DA
P 2850 2300
F 0 "P?" H 2850 2500 50  0000 C CNN
F 1 "CONN_01X03" V 2950 2300 50  0000 C CNN
F 2 "" H 2850 2300 50  0000 C CNN
F 3 "" H 2850 2300 50  0000 C CNN
	1    2850 2300
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P?
U 1 1 5E2D551B
P 2850 2850
F 0 "P?" H 2850 3050 50  0000 C CNN
F 1 "CONN_01X03" V 2950 2850 50  0000 C CNN
F 2 "" H 2850 2850 50  0000 C CNN
F 3 "" H 2850 2850 50  0000 C CNN
	1    2850 2850
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P?
U 1 1 5E2D55C0
P 2850 3450
F 0 "P?" H 2850 3650 50  0000 C CNN
F 1 "CONN_01X03" V 2950 3450 50  0000 C CNN
F 2 "" H 2850 3450 50  0000 C CNN
F 3 "" H 2850 3450 50  0000 C CNN
	1    2850 3450
	-1   0    0    1   
$EndComp
$EndSCHEMATC
