EESchema Schematic File Version 4
EELAYER 30 0
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
L mini-serre-rescue:ESP-12E-RF_Module U1
U 1 1 5E2D5255
P 2550 6400
F 0 "U1" H 2550 6300 50  0000 C CNN
F 1 "ESP-12E" H 2550 6500 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 2550 6400 50  0001 C CNN
F 3 "" H 2550 6400 50  0001 C CNN
	1    2550 6400
	1    0    0    -1  
$EndComp
Text GLabel 2750 5600 2    60   Input ~ 0
3V3
Wire Wire Line
	2750 5600 2550 5600
Wire Wire Line
	2550 7100 2550 7250
Text GLabel 3450 6200 2    50   Input ~ 0
SDA
Wire Wire Line
	3150 6200 3450 6200
Wire Wire Line
	3400 6800 3150 6800
Wire Wire Line
	3400 6400 3150 6400
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0101
U 1 1 5E2F6513
P 4650 5800
F 0 "#PWR0101" H 4650 5600 50  0001 C CNN
F 1 "GNDPWR" H 4654 5646 50  0000 C CNN
F 2 "" H 4650 5750 50  0001 C CNN
F 3 "" H 4650 5750 50  0001 C CNN
	1    4650 5800
	-1   0    0    1   
$EndComp
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0102
U 1 1 5E2F6A10
P 2550 7250
F 0 "#PWR0102" H 2550 7050 50  0001 C CNN
F 1 "GNDPWR" H 2554 7096 50  0000 C CNN
F 2 "" H 2550 7200 50  0001 C CNN
F 3 "" H 2550 7200 50  0001 C CNN
	1    2550 7250
	1    0    0    -1  
$EndComp
Wire Notes Line
	500  500  500  3600
$Comp
L mini-serre-rescue:R-Device R8
U 1 1 5E2FBA44
P 1350 5050
F 0 "R8" H 1420 5096 50  0000 L CNN
F 1 "10k" H 1420 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 1280 5050 50  0001 C CNN
F 3 "~" H 1350 5050 50  0001 C CNN
	1    1350 5050
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:R-Device R7
U 1 1 5E2FC6FC
P 1650 5050
F 0 "R7" H 1720 5096 50  0000 L CNN
F 1 "10k" H 1720 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 1580 5050 50  0001 C CNN
F 3 "~" H 1650 5050 50  0001 C CNN
	1    1650 5050
	1    0    0    -1  
$EndComp
Text GLabel 3450 5800 2    50   Input ~ 0
IO0
Text GLabel 3450 6000 2    50   Input ~ 0
IO2
Wire Wire Line
	3150 5800 3450 5800
Wire Wire Line
	3450 6000 3150 6000
Text GLabel 1350 5350 3    50   Input ~ 0
IO2
Text GLabel 1650 5350 3    50   Input ~ 0
CH_PD
Wire Wire Line
	1500 4700 1500 4800
Wire Wire Line
	1500 4800 1650 4800
Wire Wire Line
	1650 4800 1650 4900
Wire Wire Line
	1500 4800 1350 4800
Wire Wire Line
	1350 4800 1350 4900
Connection ~ 1500 4800
Wire Wire Line
	1350 5200 1350 5350
Wire Wire Line
	1650 5200 1650 5350
Text GLabel 1700 6000 0    50   Input ~ 0
CH_PD
Wire Wire Line
	1950 6000 1700 6000
Text GLabel 1700 5800 0    50   Input ~ 0
RESET
Wire Wire Line
	1700 5800 1950 5800
$Comp
L mini-serre-rescue:R-Device R6
U 1 1 5E3482C2
P 2000 5050
F 0 "R6" H 2070 5096 50  0000 L CNN
F 1 "4.7k" H 2070 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 1930 5050 50  0001 C CNN
F 3 "~" H 2000 5050 50  0001 C CNN
	1    2000 5050
	1    0    0    -1  
$EndComp
Text GLabel 2000 5350 3    50   Input ~ 0
IO15
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0104
U 1 1 5E349003
P 2000 4800
F 0 "#PWR0104" H 2000 4600 50  0001 C CNN
F 1 "GNDPWR" H 2005 4645 50  0000 C CNN
F 2 "" H 2000 4750 50  0001 C CNN
F 3 "" H 2000 4750 50  0001 C CNN
	1    2000 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 4800 2000 4900
Wire Wire Line
	2000 5200 2000 5350
$Comp
L mini-serre-rescue:CD74HC4067M-74xx U5
U 1 1 5E47FBFB
P 4350 2100
F 0 "U5" H 4350 819 50  0000 C CNN
F 1 "CD74HC4067M" H 4350 910 50  0000 C CNN
F 2 "Package_SO:SOIC-24W_7.5x15.4mm_P1.27mm" H 5250 1100 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/cd74hc4067.pdf" H 4000 2950 50  0001 C CNN
	1    4350 2100
	-1   0    0    1   
$EndComp
$Comp
L mini-serre:MC74HC161A U4
U 1 1 5E49B122
P 5850 2050
F 0 "U4" H 5825 1435 50  0000 C CNN
F 1 "MC74HC161A" H 5825 1526 50  0000 C CNN
F 2 "Package_SO:SOIC-16_4.55x10.3mm_P1.27mm" H 5750 2250 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/308/MC74HC161A-D-96932.pdf" H 5750 2250 50  0001 C CNN
	1    5850 2050
	-1   0    0    1   
$EndComp
Text GLabel 3400 6500 2    50   Input ~ 0
SEL
Wire Wire Line
	3400 6500 3150 6500
Text GLabel 6750 2500 2    50   Input ~ 0
3V3
Wire Wire Line
	6600 1900 6400 1900
Wire Wire Line
	6600 1900 6600 2000
Wire Wire Line
	6600 2000 6400 2000
Connection ~ 6600 1900
Wire Wire Line
	6600 2000 6600 2100
Wire Wire Line
	6600 2100 6400 2100
Connection ~ 6600 2000
Wire Wire Line
	6400 1700 6600 1700
Connection ~ 6600 1700
Wire Wire Line
	6600 2100 6600 2200
Wire Wire Line
	6600 2200 6400 2200
Connection ~ 6600 2100
Wire Wire Line
	6400 2400 6500 2400
Wire Wire Line
	6600 1400 6600 1500
Text GLabel 7150 2300 2    50   Input ~ 0
SEL
Wire Wire Line
	5150 1700 5350 1700
Wire Wire Line
	5350 2400 5150 2400
Connection ~ 5150 2400
Wire Wire Line
	5150 2400 5150 1800
Wire Wire Line
	6600 2400 6600 2500
Wire Wire Line
	6600 2600 5150 2600
Wire Wire Line
	5150 2600 5150 2400
Wire Wire Line
	6400 1000 6400 1500
Wire Wire Line
	6400 1500 6600 1500
Connection ~ 6600 1500
Wire Wire Line
	6600 1500 6600 1700
Wire Wire Line
	4350 1000 4950 1000
Wire Wire Line
	4850 1900 5350 1900
Wire Wire Line
	4850 2000 5350 2000
Wire Wire Line
	4850 2100 5350 2100
Wire Wire Line
	4850 2200 5350 2200
Wire Wire Line
	4850 1500 4950 1500
Wire Wire Line
	4950 1500 4950 1000
Connection ~ 4950 1000
Text GLabel 1700 6200 0    50   Input ~ 0
MM
Wire Wire Line
	1950 6200 1700 6200
$Comp
L mini-serre-rescue:R-Device R10
U 1 1 5E51C0F3
P 4950 2850
F 0 "R10" H 5020 2896 50  0000 L CNN
F 1 "4k7" H 5020 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4880 2850 50  0001 C CNN
F 3 "~" H 4950 2850 50  0001 C CNN
	1    4950 2850
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:R-Device R11
U 1 1 5E51CAC6
P 4950 3250
F 0 "R11" H 5020 3296 50  0000 L CNN
F 1 "2k" H 5020 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4880 3250 50  0001 C CNN
F 3 "~" H 4950 3250 50  0001 C CNN
	1    4950 3250
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:Conn_02x16_Odd_Even-Connector_Generic J3
U 1 1 5E5330C3
P 1300 2000
F 0 "J3" H 1350 2917 50  0000 C CNN
F 1 "SEN" H 1350 2826 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x16_P2.54mm_Vertical_SMD" H 1300 2000 50  0001 C CNN
F 3 "~" H 1300 2000 50  0001 C CNN
	1    1300 2000
	1    0    0    -1  
$EndComp
Text GLabel 5200 3050 2    50   Input ~ 0
MM
Wire Wire Line
	4850 2600 4950 2600
Wire Wire Line
	4950 2600 4950 2700
Wire Wire Line
	4950 3000 4950 3050
Wire Wire Line
	5200 3050 4950 3050
Connection ~ 4950 3050
Wire Wire Line
	4950 3050 4950 3100
$Comp
L mini-serre:EXBA R13
U 1 1 5E67E3B9
P 2250 3350
F 0 "R13" V 2179 3678 50  0000 L CNN
F 1 "10k" V 2270 3678 50  0000 L CNN
F 2 "mini-serre:R_Array_Convex_5x1206" H 2600 3300 50  0001 C CNN
F 3 "" H 2600 3300 50  0001 C CNN
	1    2250 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 3900 2150 3900
Wire Wire Line
	3100 3900 3100 3700
Wire Wire Line
	2050 3700 2050 3900
Wire Wire Line
	3000 3700 3000 3900
Connection ~ 3000 3900
Wire Wire Line
	3000 3900 3100 3900
Wire Wire Line
	2150 3700 2150 3900
Connection ~ 2150 3900
Wire Wire Line
	2150 3900 3000 3900
Wire Wire Line
	4950 3400 4950 3900
Wire Wire Line
	4950 3900 3300 3900
Connection ~ 3100 3900
Text GLabel 4350 3250 3    50   Input ~ 0
3V3
Wire Wire Line
	4350 3250 4350 3100
Text GLabel 900  1000 1    50   Input ~ 0
3V3
Wire Wire Line
	900  1000 900  1300
Wire Wire Line
	900  1300 1100 1300
Wire Wire Line
	900  1300 900  1400
Wire Wire Line
	900  1400 1100 1400
Connection ~ 900  1300
Wire Wire Line
	900  1400 900  1500
Wire Wire Line
	900  1500 1100 1500
Connection ~ 900  1400
Wire Wire Line
	900  1500 900  1600
Wire Wire Line
	900  1600 1100 1600
Connection ~ 900  1500
Wire Wire Line
	900  1600 900  1700
Wire Wire Line
	900  1700 1100 1700
Connection ~ 900  1600
Wire Wire Line
	900  1700 900  1800
Wire Wire Line
	900  1800 1100 1800
Connection ~ 900  1700
Wire Wire Line
	900  1800 900  1900
Wire Wire Line
	900  1900 1100 1900
Connection ~ 900  1800
Wire Wire Line
	900  1900 900  2000
Wire Wire Line
	900  2000 1100 2000
Connection ~ 900  1900
Wire Wire Line
	900  2000 900  2100
Wire Wire Line
	900  2100 1100 2100
Connection ~ 900  2000
Wire Wire Line
	900  2100 900  2200
Wire Wire Line
	900  2200 1100 2200
Connection ~ 900  2100
Wire Wire Line
	900  2200 900  2300
Wire Wire Line
	900  2300 1100 2300
Connection ~ 900  2200
Wire Wire Line
	900  2300 900  2400
Wire Wire Line
	900  2400 1100 2400
Connection ~ 900  2300
Wire Wire Line
	900  2400 900  2500
Wire Wire Line
	900  2500 1100 2500
Connection ~ 900  2400
Wire Wire Line
	900  2500 900  2600
Wire Wire Line
	900  2600 1100 2600
Connection ~ 900  2500
Wire Wire Line
	900  2600 900  2700
Wire Wire Line
	900  2700 1100 2700
Connection ~ 900  2600
Wire Wire Line
	900  2700 900  2800
Wire Wire Line
	900  2800 1100 2800
Connection ~ 900  2700
Wire Wire Line
	5350 2300 5250 2300
Wire Wire Line
	5250 2300 5250 2750
Wire Wire Line
	6750 2500 6600 2500
Connection ~ 6600 2500
Wire Wire Line
	6600 2500 6600 2600
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0106
U 1 1 5E8B7A78
P 3300 3900
F 0 "#PWR0106" H 3300 3700 50  0001 C CNN
F 1 "GNDPWR" H 3304 3746 50  0000 C CNN
F 2 "" H 3300 3850 50  0001 C CNN
F 3 "" H 3300 3850 50  0001 C CNN
	1    3300 3900
	1    0    0    -1  
$EndComp
Connection ~ 3300 3900
Wire Wire Line
	3300 3900 3100 3900
$Comp
L mini-serre:IMH20TR1G Q1
U 1 1 5E8D1517
P 3450 5050
F 0 "Q1" H 3450 4700 50  0000 C CNN
F 1 "IMH20TR1G" H 3450 4800 50  0000 C CNN
F 2 "Package_SO:SC-74-6_1.5x2.9mm_P0.95mm" H 3450 5000 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/IMH20TR1G.PDF" H 3450 5000 50  0001 C CNN
	1    3450 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 5050 4200 5050
Wire Wire Line
	4200 5050 4200 4850
Wire Wire Line
	4200 4850 3050 4850
Wire Wire Line
	3050 4850 3050 4900
Wire Wire Line
	3050 5050 2500 5050
Wire Wire Line
	2500 5050 2500 5250
Wire Wire Line
	2500 5250 3850 5250
Wire Wire Line
	3850 5250 3850 5200
Text GLabel 3850 4950 2    50   Input ~ 0
IO0
Text GLabel 3050 5150 0    50   Input ~ 0
RESET
Text GLabel 3000 4900 0    50   Input ~ 0
RTS
Text GLabel 3900 5200 2    50   Input ~ 0
DTR
Wire Wire Line
	3900 5200 3850 5200
Connection ~ 3850 5200
Wire Wire Line
	3850 5200 3850 5150
Wire Wire Line
	3000 4900 3050 4900
Connection ~ 3050 4900
Wire Wire Line
	3050 4900 3050 4950
$Comp
L mini-serre-rescue:Barrel_Jack_Switch-Connector J0
U 1 1 5E92F582
P 6900 5150
F 0 "J0" V 6900 4950 50  0000 L CNN
F 1 "POWER" V 7000 4800 50  0000 L CNN
F 2 "mini-serre:BarrelJack_Wuerth_6941xx301002" H 6900 5150 50  0001 C CNN
F 3 "~" H 6900 5150 50  0001 C CNN
	1    6900 5150
	1    0    0    -1  
$EndComp
Text GLabel 10000 4800 2    50   Input ~ 0
3V3
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0107
U 1 1 5E97EF4E
P 8250 5500
F 0 "#PWR0107" H 8250 5300 50  0001 C CNN
F 1 "GNDPWR" H 8254 5346 50  0000 C CNN
F 2 "" H 8250 5450 50  0001 C CNN
F 3 "" H 8250 5450 50  0001 C CNN
	1    8250 5500
	1    0    0    -1  
$EndComp
Text GLabel 3400 6400 2    50   Input ~ 0
SIG1
Text GLabel 3400 6800 2    50   Input ~ 0
RESET
Text GLabel 3250 7000 3    50   Input ~ 0
SIG3
$Comp
L mini-serre:VNN3NV04PTR Q3
U 1 1 5E6C5078
P 9800 2650
F 0 "Q3" H 9775 2965 50  0000 C CNN
F 1 "VNN3NV04PTR" H 9775 2874 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 9750 2500 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/389/vnn3nv04p-e-957619.pdf" H 9750 2500 50  0001 C CNN
	1    9800 2650
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:R-Device R1
U 1 1 5E6C97A0
P 9100 2650
F 0 "R1" V 8893 2650 50  0000 C CNN
F 1 "220" V 8984 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 9030 2650 50  0001 C CNN
F 3 "~" H 9100 2650 50  0001 C CNN
	1    9100 2650
	0    1    1    0   
$EndComp
$Comp
L mini-serre-rescue:Conn_02x03_Odd_Even-Connector_Generic J2
U 1 1 5E6DB0FC
P 10000 1700
F 0 "J2" H 10050 1375 50  0000 C CNN
F 1 "ACT" H 10050 1466 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical_SMD" H 10000 1700 50  0001 C CNN
F 3 "~" H 10000 1700 50  0001 C CNN
	1    10000 1700
	-1   0    0    1   
$EndComp
Text GLabel 8900 1000 0    50   Input ~ 0
12V
Text GLabel 10400 1600 2    50   Input ~ 0
D1
Text GLabel 10400 1700 2    50   Input ~ 0
D2
Text GLabel 10400 1800 2    50   Input ~ 0
D3
Text GLabel 8950 3550 0    50   Input ~ 0
SIG2
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0109
U 1 1 5E7D944A
P 10300 2700
F 0 "#PWR0109" H 10300 2500 50  0001 C CNN
F 1 "GNDPWR" H 10304 2546 50  0000 C CNN
F 2 "" H 10300 2650 50  0001 C CNN
F 3 "" H 10300 2650 50  0001 C CNN
	1    10300 2700
	1    0    0    -1  
$EndComp
$Comp
L mini-serre:VNN3NV04PTR Q4
U 1 1 5E7F8390
P 7500 3600
F 0 "Q4" H 7475 3915 50  0000 C CNN
F 1 "VNN3NV04PTR" H 7475 3824 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 7450 3450 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/389/vnn3nv04p-e-957619.pdf" H 7450 3450 50  0001 C CNN
	1    7500 3600
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:R-Device R3
U 1 1 5E7F839A
P 6800 3600
F 0 "R3" V 6593 3600 50  0000 C CNN
F 1 "220" V 6684 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 6730 3600 50  0001 C CNN
F 3 "~" H 6800 3600 50  0001 C CNN
	1    6800 3600
	0    1    1    0   
$EndComp
Text GLabel 6650 3600 0    50   Input ~ 0
SIG3
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0110
U 1 1 5E7F83A5
P 8000 3650
F 0 "#PWR0110" H 8000 3450 50  0001 C CNN
F 1 "GNDPWR" H 8004 3496 50  0000 C CNN
F 2 "" H 8000 3600 50  0001 C CNN
F 3 "" H 8000 3600 50  0001 C CNN
	1    8000 3650
	1    0    0    -1  
$EndComp
Text GLabel 8100 3550 2    50   Input ~ 0
D3
$Comp
L mini-serre:VNN3NV04PTR Q2
U 1 1 5E83B796
P 9800 3550
F 0 "Q2" H 9775 3865 50  0000 C CNN
F 1 "VNN3NV04PTR" H 9775 3774 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 9750 3400 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/389/vnn3nv04p-e-957619.pdf" H 9750 3400 50  0001 C CNN
	1    9800 3550
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:R-Device R2
U 1 1 5E83B7A0
P 9100 3550
F 0 "R2" V 8893 3550 50  0000 C CNN
F 1 "220" V 8984 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 9030 3550 50  0001 C CNN
F 3 "~" H 9100 3550 50  0001 C CNN
	1    9100 3550
	0    1    1    0   
$EndComp
Text GLabel 8950 2650 0    50   Input ~ 0
SIG1
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0111
U 1 1 5E83B7AB
P 10300 3600
F 0 "#PWR0111" H 10300 3400 50  0001 C CNN
F 1 "GNDPWR" H 10304 3446 50  0000 C CNN
F 2 "" H 10300 3550 50  0001 C CNN
F 3 "" H 10300 3550 50  0001 C CNN
	1    10300 3600
	1    0    0    -1  
$EndComp
Text GLabel 10400 3500 2    50   Input ~ 0
D1
$Comp
L mini-serre:EXBA R12
U 1 1 5E5B08EE
P 3200 3350
F 0 "R12" V 3129 3678 50  0000 L CNN
F 1 "10k" V 3220 3678 50  0000 L CNN
F 2 "mini-serre:R_Array_Convex_5x1206" H 3550 3300 50  0001 C CNN
F 3 "" H 3550 3300 50  0001 C CNN
	1    3200 3350
	0    1    1    0   
$EndComp
$Comp
L mini-serre-rescue:Conn_02x03_Counter_Clockwise-Connector_Generic J1
U 1 1 5E9F7DEB
P 4450 6100
F 0 "J1" H 4500 6417 50  0000 C CNN
F 1 "SERIAL" H 4500 6326 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical_SMD" H 4450 6100 50  0001 C CNN
F 3 "~" H 4450 6100 50  0001 C CNN
	1    4450 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 6300 3450 6300
Text GLabel 3450 6300 2    50   Input ~ 0
SCL
Wire Wire Line
	4650 5800 4650 5850
Wire Wire Line
	3400 6600 3150 6600
Text GLabel 3400 6600 2    50   Input ~ 0
SIG2
Text GLabel 3400 6700 2    50   Input ~ 0
IO15
Wire Wire Line
	3150 6700 3250 6700
Wire Wire Line
	4650 5850 4150 5850
Wire Wire Line
	4150 5850 4150 6000
Connection ~ 4650 5850
Wire Wire Line
	4650 5850 4650 6000
Wire Wire Line
	3250 7000 3250 6700
Connection ~ 3250 6700
Wire Wire Line
	3250 6700 3400 6700
Text GLabel 4150 6100 0    50   Input ~ 0
DTR
Text GLabel 4150 6200 0    50   Input ~ 0
RTS
Wire Wire Line
	4650 6100 4900 6100
Wire Wire Line
	4900 6100 4900 5500
Wire Wire Line
	4900 5500 3850 5500
Wire Wire Line
	3850 5500 3850 5900
Wire Wire Line
	3850 5900 3150 5900
Wire Wire Line
	3150 6100 3850 6100
Wire Wire Line
	3850 6100 3850 6550
Wire Wire Line
	3850 6550 4900 6550
Wire Wire Line
	4900 6550 4900 6200
Wire Wire Line
	4900 6200 4650 6200
Text GLabel 1500 4700 1    50   Input ~ 0
3V3
Wire Wire Line
	1600 2700 2150 2700
Wire Wire Line
	1600 2800 2050 2800
Wire Wire Line
	1600 2100 2450 2100
Wire Wire Line
	1600 2200 1750 2200
Wire Wire Line
	1600 2000 3400 2000
Wire Wire Line
	1600 1900 2700 1900
Wire Wire Line
	1600 1800 3300 1800
Wire Wire Line
	1600 1700 2800 1700
Wire Wire Line
	1600 1300 3000 1300
Wire Wire Line
	1600 1400 3100 1400
Wire Wire Line
	1600 1500 2900 1500
Wire Wire Line
	1600 1600 3200 1600
Wire Wire Line
	2050 2950 2050 2800
Connection ~ 2050 2800
Wire Wire Line
	2050 2800 3850 2800
Wire Wire Line
	2150 2950 2150 2700
Connection ~ 2150 2700
Wire Wire Line
	2150 2700 3850 2700
Wire Wire Line
	1600 2400 1850 2400
Wire Wire Line
	1600 2300 2350 2300
Wire Wire Line
	1600 2600 1950 2600
Wire Wire Line
	1600 2500 2250 2500
Wire Wire Line
	1950 2950 1950 2600
Connection ~ 1950 2600
Wire Wire Line
	1950 2600 3850 2600
Wire Wire Line
	2250 2950 2250 2500
Connection ~ 2250 2500
Wire Wire Line
	2250 2500 3850 2500
Wire Wire Line
	1850 2950 1850 2400
Connection ~ 1850 2400
Wire Wire Line
	1850 2400 3850 2400
Wire Wire Line
	2350 2950 2350 2300
Connection ~ 2350 2300
Wire Wire Line
	2350 2300 3850 2300
Wire Wire Line
	1750 2950 1750 2200
Connection ~ 1750 2200
Wire Wire Line
	1750 2200 3850 2200
Wire Wire Line
	2450 2950 2450 2100
Connection ~ 2450 2100
Wire Wire Line
	3000 2950 3000 1300
Connection ~ 3000 1300
Wire Wire Line
	3000 1300 3850 1300
Wire Wire Line
	3100 2950 3100 1400
Connection ~ 3100 1400
Wire Wire Line
	3100 1400 3850 1400
Wire Wire Line
	2900 2950 2900 1500
Connection ~ 2900 1500
Wire Wire Line
	2900 1500 3850 1500
Wire Wire Line
	3200 2950 3200 1600
Connection ~ 3200 1600
Wire Wire Line
	3200 1600 3850 1600
Wire Wire Line
	2800 2950 2800 1700
Connection ~ 2800 1700
Wire Wire Line
	2800 1700 3850 1700
Wire Wire Line
	3300 2950 3300 1800
Connection ~ 3300 1800
Wire Wire Line
	3300 1800 3850 1800
Wire Wire Line
	2700 2950 2700 1900
Connection ~ 2700 1900
Wire Wire Line
	2700 1900 3850 1900
Wire Wire Line
	2450 2100 3850 2100
Wire Wire Line
	3400 2950 3400 2000
Connection ~ 3400 2000
Wire Wire Line
	3400 2000 3850 2000
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0103
U 1 1 5E9F37F9
P 6600 1400
F 0 "#PWR0103" H 6600 1200 50  0001 C CNN
F 1 "GNDPWR" H 6605 1245 50  0000 C CNN
F 2 "" H 6600 1350 50  0001 C CNN
F 3 "" H 6600 1350 50  0001 C CNN
	1    6600 1400
	-1   0    0    1   
$EndComp
$Comp
L mini-serre-rescue:Conn_02x02_Counter_Clockwise-Connector_Generic J4
U 1 1 5EA19A4C
P 4750 4550
F 0 "J4" H 4800 4767 50  0000 C CNN
F 1 "I2C" H 4800 4676 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical_SMD" H 4750 4550 50  0001 C CNN
F 3 "~" H 4750 4550 50  0001 C CNN
	1    4750 4550
	1    0    0    -1  
$EndComp
Text GLabel 5050 4550 2    50   Input ~ 0
3V3
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0112
U 1 1 5EA1B4FE
P 5050 4650
F 0 "#PWR0112" H 5050 4450 50  0001 C CNN
F 1 "GNDPWR" H 5054 4496 50  0000 C CNN
F 2 "" H 5050 4600 50  0001 C CNN
F 3 "" H 5050 4600 50  0001 C CNN
	1    5050 4650
	1    0    0    -1  
$EndComp
Text GLabel 4550 4550 0    50   Input ~ 0
SDA
Text GLabel 4550 4650 0    50   Input ~ 0
SCL
$Comp
L mini-serre-rescue:Conn_02x04_Odd_Even-Connector_Generic J5
U 1 1 5EA1E0DA
P 1250 6600
F 0 "J5" V 1254 6780 50  0000 L CNN
F 1 "EXT" V 1345 6780 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical_SMD" H 1250 6600 50  0001 C CNN
F 3 "~" H 1250 6600 50  0001 C CNN
	1    1250 6600
	1    0    0    -1  
$EndComp
$Comp
L mini-serre-rescue:GNDPWR-power #PWR0113
U 1 1 5EAC8FE6
P 1050 6800
F 0 "#PWR0113" H 1050 6600 50  0001 C CNN
F 1 "GNDPWR" H 1055 6645 50  0000 C CNN
F 2 "" H 1050 6750 50  0001 C CNN
F 3 "" H 1050 6750 50  0001 C CNN
	1    1050 6800
	0    1    1    0   
$EndComp
Text GLabel 1050 6500 0    50   Input ~ 0
3V3
Text GLabel 7100 4850 0    50   Input ~ 0
12V
Text GLabel 6950 3700 0    50   Input ~ 0
D3
Text GLabel 10400 2600 2    50   Input ~ 0
D2
Text GLabel 9250 2750 0    50   Input ~ 0
D2
Text GLabel 9250 3650 0    50   Input ~ 0
D1
Wire Wire Line
	1950 6400 1550 6400
Wire Wire Line
	1550 6400 1550 6500
Wire Wire Line
	1950 6500 1650 6500
Wire Wire Line
	1650 6500 1650 6600
Wire Wire Line
	1650 6600 1550 6600
Wire Wire Line
	1950 6800 1700 6800
Wire Wire Line
	1700 6800 1700 6700
Wire Wire Line
	1700 6700 1550 6700
Wire Wire Line
	1950 6900 1650 6900
Wire Wire Line
	1650 6900 1650 6800
Wire Wire Line
	1650 6800 1550 6800
Text GLabel 1950 6700 0    50   Input ~ 0
IO10
Text GLabel 1950 6600 0    50   Input ~ 0
IO9
Text GLabel 1050 6700 0    50   Input ~ 0
IO10
Text GLabel 1050 6600 0    50   Input ~ 0
IO9
Wire Wire Line
	4950 1000 6400 1000
Wire Wire Line
	6600 1700 6600 1900
Wire Wire Line
	6400 1800 6500 1800
Wire Wire Line
	6500 1800 6500 2400
Connection ~ 6500 2400
Wire Wire Line
	6500 2400 6600 2400
Wire Wire Line
	5150 1800 5350 1800
Connection ~ 5150 1800
Wire Wire Line
	5150 1800 5150 1700
$Comp
L mini-serre-rescue:R-Device R9
U 1 1 5E889D2B
P 5850 2750
F 0 "R9" H 5780 2704 50  0000 R CNN
F 1 "10k" H 5780 2795 50  0000 R CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 5780 2750 50  0001 C CNN
F 3 "~" H 5850 2750 50  0001 C CNN
	1    5850 2750
	0    -1   -1   0   
$EndComp
$Comp
L mini-serre-rescue:D_Schottky-Device D4
U 1 1 5E954EFD
P 6850 2300
F 0 "D4" H 6850 2084 50  0000 C CNN
F 1 "D_SHOTTKY" H 6850 2175 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 6850 2300 50  0001 C CNN
F 3 "https://shop.boxtec.ch/pub/diverse/ds30217.pdf" H 6850 2300 50  0001 C CNN
	1    6850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2750 5700 2750
Wire Wire Line
	6000 2750 7050 2750
Wire Wire Line
	7050 2750 7050 2300
Wire Wire Line
	7150 2300 7050 2300
Wire Wire Line
	7050 2300 7000 2300
Connection ~ 7050 2300
Wire Wire Line
	6400 2300 6700 2300
$Comp
L Regulator_Switching:AP65111AWU U2
U 1 1 5EACE685
P 8250 4950
F 0 "U2" H 8250 5317 50  0000 C CNN
F 1 "AP65111AWU" H 8250 5226 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-6" H 8250 4050 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP65111A.pdf" H 8250 4950 50  0001 C CNN
	1    8250 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5EAD16C2
P 9200 4800
F 0 "L1" V 9390 4800 50  0000 C CNN
F 1 "6.5uH" V 9299 4800 50  0000 C CNN
F 2 "Inductor_SMD:L_Taiyo-Yuden_NR-10050_9.8x10.0mm_HandSoldering" H 9200 4800 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/396/wound06_e-1313806.pdf" H 9200 4800 50  0001 C CNN
F 4 "963-NR10050T6R5N" V 9200 4800 50  0001 C CNN "Mouser"
	1    9200 4800
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C2
U 1 1 5EAD21B4
P 8800 4950
F 0 "C2" V 9052 4950 50  0000 C CNN
F 1 "1uF" V 8961 4950 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8838 4800 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/212/KEM_C1006_X5R_SMD-1103249.pdf" H 8800 4950 50  0001 C CNN
	1    8800 4950
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5EAD3240
P 9800 5100
F 0 "C3" H 9915 5146 50  0000 L CNN
F 1 "22uF" H 9915 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9838 4950 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/212/KEM_C1006_X5R_SMD-1103249.pdf" H 9800 5100 50  0001 C CNN
	1    9800 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5EAD4E49
P 7450 5150
F 0 "C1" H 7565 5196 50  0000 L CNN
F 1 "22uF" H 7565 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7488 5000 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/212/KEM_C1006_X5R_SMD-1103249.pdf" H 7450 5150 50  0001 C CNN
	1    7450 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 5EAD77D8
P 9400 4950
F 0 "R16" H 9470 4996 50  0000 L CNN
F 1 "40.2k" H 9470 4905 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9330 4950 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/54/chpreztr-777398.pdf" H 9400 4950 50  0001 C CNN
F 4 "652-CR1206FX-4022ELF " H 9400 4950 50  0001 C CNN "Mouser"
	1    9400 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5EAD830B
P 9200 5150
F 0 "R15" V 8993 5150 50  0000 C CNN
F 1 "59k" V 9084 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9130 5150 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/315/AOA0000C304-1149620.pdf" H 9200 5150 50  0001 C CNN
F 4 "667-ERJ-8ENF5902V" V 9200 5150 50  0001 C CNN "Mouser"
	1    9200 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 5EAD8B39
P 9400 5350
F 0 "R17" H 9470 5396 50  0000 L CNN
F 1 "13k" H 9470 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9330 5350 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/315/AOA0000C304-1149620.pdf" H 9400 5350 50  0001 C CNN
F 4 "667-ERJ-8ENF1302V " H 9400 5350 50  0001 C CNN "Mouser"
	1    9400 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 4850 8700 4850
Wire Wire Line
	8700 4850 8700 4800
Wire Wire Line
	8950 4950 8950 4800
Connection ~ 8950 4800
Wire Wire Line
	8950 4800 9050 4800
Wire Wire Line
	8650 5050 8700 5050
Wire Wire Line
	8700 5050 8700 5150
Wire Wire Line
	8700 5150 9050 5150
Wire Wire Line
	9350 5150 9400 5150
Wire Wire Line
	9400 5150 9400 5100
Wire Wire Line
	9400 5150 9400 5200
Connection ~ 9400 5150
Wire Wire Line
	9350 4800 9400 4800
Wire Wire Line
	8250 5250 8250 5500
Wire Wire Line
	8250 5500 9400 5500
Wire Wire Line
	7450 5500 8250 5500
Connection ~ 8250 5500
Wire Wire Line
	7450 5000 7450 4850
Wire Wire Line
	7450 4850 7700 4850
Wire Wire Line
	9400 4800 9800 4800
Wire Wire Line
	9800 4800 9800 4950
Connection ~ 9400 4800
Wire Wire Line
	9800 5250 9800 5500
Wire Wire Line
	9800 5500 9400 5500
Connection ~ 9400 5500
Wire Wire Line
	7200 5150 7200 5250
Wire Wire Line
	7450 5300 7450 5500
Wire Wire Line
	7200 5250 7200 5500
Wire Wire Line
	7200 5500 7450 5500
Connection ~ 7200 5250
Connection ~ 7450 5500
Wire Wire Line
	7200 5050 7200 4850
Wire Wire Line
	7200 4850 7450 4850
Connection ~ 7450 4850
Wire Wire Line
	9800 4800 10000 4800
Connection ~ 9800 4800
Wire Wire Line
	7100 4850 7200 4850
Connection ~ 7200 4850
$Comp
L Device:D_Zener D1
U 1 1 5F04AB6D
P 9250 1350
F 0 "D1" H 9250 1567 50  0000 C CNN
F 1 "D_Zener" H 9250 1476 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 9250 1350 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/427/bzg05c-m-series-1767829.pdf" H 9250 1350 50  0001 C CNN
F 4 "78-BZG05C5V6-M3-08 " H 9250 1350 50  0001 C CNN "Mouser"
	1    9250 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 5F04F779
P 9250 1700
F 0 "D2" H 9250 1917 50  0000 C CNN
F 1 "D_Zener" H 9250 1826 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 9250 1700 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/427/bzg05c-m-series-1767829.pdf" H 9250 1700 50  0001 C CNN
F 4 "78-BZG05C5V6-M3-08" H 9250 1700 50  0001 C CNN "Mouser"
	1    9250 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 5F051B47
P 9250 2050
F 0 "D3" H 9250 2267 50  0000 C CNN
F 1 "D_Zener" H 9250 2176 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 9250 2050 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/427/bzg05c-m-series-1767829.pdf" H 9250 2050 50  0001 C CNN
F 4 "78-BZG05C5V6-M3-08 " H 9250 2050 50  0001 C CNN "Mouser"
	1    9250 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1000 9000 1000
Wire Wire Line
	9000 1000 9000 1350
Wire Wire Line
	9000 1350 9100 1350
Wire Wire Line
	9000 1350 9000 1700
Wire Wire Line
	9000 1700 9100 1700
Connection ~ 9000 1350
Wire Wire Line
	9000 1700 9000 2050
Wire Wire Line
	9000 2050 9100 2050
Connection ~ 9000 1700
Wire Wire Line
	9700 1800 9500 1800
Wire Wire Line
	9500 1800 9500 2050
Wire Wire Line
	9500 1350 9500 1600
Wire Wire Line
	9500 1600 9700 1600
Wire Wire Line
	10200 1800 10400 1800
Wire Wire Line
	10200 1700 10400 1700
Wire Wire Line
	10200 1600 10400 1600
Wire Wire Line
	9400 1700 9700 1700
Wire Wire Line
	9400 1350 9500 1350
Wire Wire Line
	9400 2050 9500 2050
Wire Wire Line
	10300 2600 10400 2600
$Comp
L Device:R R14
U 1 1 5EBC3512
P 7700 5000
F 0 "R14" H 7770 5046 50  0000 L CNN
F 1 "100k" H 7770 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7630 5000 50  0001 C CNN
F 3 "https://www.mouser.ch/datasheet/2/427/crcwce3-1762584.pdf" H 7700 5000 50  0001 C CNN
F 4 "71-CRCW1206100KFKEAC" H 7700 5000 50  0001 C CNN "Mouser"
	1    7700 5000
	1    0    0    -1  
$EndComp
Connection ~ 7700 4850
Wire Wire Line
	7700 4850 7850 4850
Wire Wire Line
	7700 5150 7850 5150
Wire Wire Line
	7850 5150 7850 5050
Wire Wire Line
	8700 4800 8950 4800
Wire Wire Line
	8000 3550 8100 3550
Wire Wire Line
	10300 3500 10400 3500
$EndSCHEMATC
