EESchema Schematic File Version 2
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
LIBS:special
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
LIBS:librairie-personnelle
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "25 feb 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PIC24FJ64GA002 U2
U 1 1 530CC133
P 5600 3750
F 0 "U2" H 5600 3050 60  0000 C CNN
F 1 "PIC24FJ64GA002" H 5600 4650 60  0000 C CNN
F 2 "" H 5650 3750 60  0000 C CNN
F 3 "" H 5650 3750 60  0000 C CNN
	1    5600 3750
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 530CC14C
P 4000 3900
F 0 "X1" H 4000 4050 60  0000 C CNN
F 1 "8Mhz" H 4000 3750 60  0000 C CNN
F 2 "" H 4000 3900 60  0000 C CNN
F 3 "" H 4000 3900 60  0000 C CNN
	1    4000 3900
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 530CC162
P 4000 4400
F 0 "C2" H 4050 4500 50  0000 L CNN
F 1 "22pF" H 4050 4300 50  0000 L CNN
F 2 "" H 4000 4400 60  0000 C CNN
F 3 "" H 4000 4400 60  0000 C CNN
	1    4000 4400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 530CC16F
P 4000 3400
F 0 "C1" H 4050 3500 50  0000 L CNN
F 1 "22pF" H 4050 3300 50  0000 L CNN
F 2 "" H 4000 3400 60  0000 C CNN
F 3 "" H 4000 3400 60  0000 C CNN
	1    4000 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 530CC177
P 4000 3050
F 0 "#PWR6" H 4000 3050 30  0001 C CNN
F 1 "GND" H 4000 2980 30  0001 C CNN
F 2 "" H 4000 3050 60  0000 C CNN
F 3 "" H 4000 3050 60  0000 C CNN
	1    4000 3050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR7
U 1 1 530CC186
P 4000 4750
F 0 "#PWR7" H 4000 4750 30  0001 C CNN
F 1 "GND" H 4000 4680 30  0001 C CNN
F 2 "" H 4000 4750 60  0000 C CNN
F 3 "" H 4000 4750 60  0000 C CNN
	1    4000 4750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 530CC2DA
P 6650 4000
F 0 "#PWR12" H 6650 4000 30  0001 C CNN
F 1 "GND" H 6650 3930 30  0001 C CNN
F 2 "" H 6650 4000 60  0000 C CNN
F 3 "" H 6650 4000 60  0000 C CNN
	1    6650 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 530CC30B
P 6650 3200
F 0 "#PWR11" H 6650 3200 30  0001 C CNN
F 1 "GND" H 6650 3130 30  0001 C CNN
F 2 "" H 6650 3200 60  0000 C CNN
F 3 "" H 6650 3200 60  0000 C CNN
	1    6650 3200
	1    0    0    -1  
$EndComp
Text GLabel 6250 2650 1    60   Input ~ 0
Vdd
$Comp
L C C6
U 1 1 530CC332
P 6650 2900
F 0 "C6" H 6700 3000 50  0000 L CNN
F 1 "100nF" H 6700 2800 50  0000 L CNN
F 2 "" H 6650 2900 60  0000 C CNN
F 3 "" H 6650 2900 60  0000 C CNN
	1    6650 2900
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 530CC33F
P 7000 2900
F 0 "C9" H 7050 3000 50  0000 L CNN
F 1 "1µF" H 7050 2800 50  0000 L CNN
F 2 "" H 7000 2900 60  0000 C CNN
F 3 "" H 7000 2900 60  0000 C CNN
	1    7000 2900
	1    0    0    -1  
$EndComp
Text GLabel 4650 4200 0    60   Input ~ 0
Vdd
$Comp
L GND #PWR10
U 1 1 530CC3BC
P 4500 5150
F 0 "#PWR10" H 4500 5150 30  0001 C CNN
F 1 "GND" H 4500 5080 30  0001 C CNN
F 2 "" H 4500 5150 60  0000 C CNN
F 3 "" H 4500 5150 60  0000 C CNN
	1    4500 5150
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 530CC3C4
P 4500 4850
F 0 "C3" H 4550 4950 50  0000 L CNN
F 1 "100nF" H 4550 4750 50  0000 L CNN
F 2 "" H 4500 4850 60  0000 C CNN
F 3 "" H 4500 4850 60  0000 C CNN
	1    4500 4850
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 530CC3CA
P 4850 4850
F 0 "C5" H 4900 4950 50  0000 L CNN
F 1 "1µF" H 4900 4750 50  0000 L CNN
F 2 "" H 4850 4850 60  0000 C CNN
F 3 "" H 4850 4850 60  0000 C CNN
	1    4850 4850
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 530CC473
P 6900 4000
F 0 "C8" H 6950 4100 50  0000 L CNN
F 1 "10µF" H 6950 3900 50  0000 L CNN
F 2 "" H 6900 4000 60  0000 C CNN
F 3 "" H 6900 4000 60  0000 C CNN
	1    6900 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 530CC49F
P 6900 4300
F 0 "#PWR14" H 6900 4300 30  0001 C CNN
F 1 "GND" H 6900 4230 30  0001 C CNN
F 2 "" H 6900 4300 60  0000 C CNN
F 3 "" H 6900 4300 60  0000 C CNN
	1    6900 4300
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 530CC4CC
P 7300 4000
F 0 "C10" H 7350 4100 50  0000 L CNN
F 1 "100nF" H 7350 3900 50  0000 L CNN
F 2 "" H 7300 4000 60  0000 C CNN
F 3 "" H 7300 4000 60  0000 C CNN
	1    7300 4000
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW2
U 1 1 530CC532
P 4350 2200
F 0 "SW2" V 4500 2250 30  0000 C CNN
F 1 "reset" V 4400 2400 59  0000 C CNN
F 2 "" H 4350 2200 60  0000 C CNN
F 3 "" H 4350 2200 60  0000 C CNN
	1    4350 2200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR8
U 1 1 530CC541
P 4250 2650
F 0 "#PWR8" H 4250 2650 30  0001 C CNN
F 1 "GND" H 4250 2580 30  0001 C CNN
F 2 "" H 4250 2650 60  0000 C CNN
F 3 "" H 4250 2650 60  0000 C CNN
	1    4250 2650
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 530CC59B
P 4700 1700
F 0 "R6" V 4780 1700 50  0000 C CNN
F 1 "10K" V 4700 1700 50  0000 C CNN
F 2 "" H 4700 1700 60  0000 C CNN
F 3 "" H 4700 1700 60  0000 C CNN
	1    4700 1700
	-1   0    0    1   
$EndComp
Text GLabel 4700 1300 1    60   Input ~ 0
Vdd
$Comp
L C C4
U 1 1 530CC5AB
P 4700 2300
F 0 "C4" H 4750 2400 50  0000 L CNN
F 1 "100nF" H 4750 2200 50  0000 L CNN
F 2 "" H 4700 2300 60  0000 C CNN
F 3 "" H 4700 2300 60  0000 C CNN
	1    4700 2300
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 530CC6B2
P 4900 2650
F 0 "R7" V 4980 2650 50  0000 C CNN
F 1 "470R" V 4900 2650 50  0000 C CNN
F 2 "" H 4900 2650 60  0000 C CNN
F 3 "" H 4900 2650 60  0000 C CNN
	1    4900 2650
	1    0    0    -1  
$EndComp
Text GLabel 4750 3000 0    39   Input ~ 0
Vpp
Text GLabel 4800 3300 0    39   Input ~ 0
PGED
Text GLabel 4800 3400 0    39   Input ~ 0
PGEC
$Comp
L CONN_5 P1
U 1 1 530CC7A9
P 1850 2350
F 0 "P1" V 1800 2350 50  0000 C CNN
F 1 "ICSP" V 1900 2350 50  0000 C CNN
F 2 "" H 1850 2350 60  0000 C CNN
F 3 "" H 1850 2350 60  0000 C CNN
	1    1850 2350
	-1   0    0    1   
$EndComp
Text GLabel 2400 2550 2    39   Input ~ 0
Vpp
Text GLabel 2400 2250 2    39   Input ~ 0
PGED
Text GLabel 2400 2150 2    39   Input ~ 0
PGEC
Text GLabel 2400 2450 2    39   Input ~ 0
Vdd
$Comp
L GND #PWR4
U 1 1 530CC881
P 2700 2400
F 0 "#PWR4" H 2700 2400 30  0001 C CNN
F 1 "GND" H 2700 2330 30  0001 C CNN
F 2 "" H 2700 2400 60  0000 C CNN
F 3 "" H 2700 2400 60  0000 C CNN
	1    2700 2400
	1    0    0    -1  
$EndComp
$Comp
L RCA_JACK J1
U 1 1 530CC90C
P 8200 4700
F 0 "J1" H 8200 4800 60  0000 C CNN
F 1 "video out" V 8200 5150 60  0000 C CNN
F 2 "~" H 8200 4700 60  0000 C CNN
F 3 "~" H 8200 4700 60  0000 C CNN
	1    8200 4700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR19
U 1 1 530CC91B
P 8200 5250
F 0 "#PWR19" H 8200 5250 30  0001 C CNN
F 1 "GND" H 8200 5180 30  0001 C CNN
F 2 "" H 8200 5250 60  0000 C CNN
F 3 "" H 8200 5250 60  0000 C CNN
	1    8200 5250
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 530CC92A
P 7350 4700
F 0 "R10" V 7430 4700 50  0000 C CNN
F 1 "75R" V 7350 4700 50  0000 C CNN
F 2 "" H 7350 4700 60  0000 C CNN
F 3 "" H 7350 4700 60  0000 C CNN
	1    7350 4700
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 530CC937
P 7350 4950
F 0 "R11" V 7430 4950 50  0000 C CNN
F 1 "470R" V 7350 4950 50  0000 C CNN
F 2 "" H 7350 4950 60  0000 C CNN
F 3 "" H 7350 4950 60  0000 C CNN
	1    7350 4950
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 530CC93F
P 6800 4700
F 0 "D2" H 6800 4800 40  0000 C CNN
F 1 "DIODE" H 6800 4600 40  0000 C CNN
F 2 "" H 6800 4700 60  0000 C CNN
F 3 "" H 6800 4700 60  0000 C CNN
	1    6800 4700
	1    0    0    -1  
$EndComp
$Comp
L CONN_7 P4
U 1 1 530CCABD
P 8400 1300
F 0 "P4" V 8370 1300 60  0000 C CNN
F 1 "gamepad 1" V 8470 1300 60  0000 C CNN
F 2 "" H 8400 1300 60  0000 C CNN
F 3 "" H 8400 1300 60  0000 C CNN
	1    8400 1300
	1    0    0    -1  
$EndComp
$Comp
L CONN_7 P5
U 1 1 530CCACA
P 8400 2200
F 0 "P5" V 8370 2200 60  0000 C CNN
F 1 "gamepad 2" V 8470 2200 60  0000 C CNN
F 2 "" H 8400 2200 60  0000 C CNN
F 3 "" H 8400 2200 60  0000 C CNN
	1    8400 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 530CCADC
P 8050 2600
F 0 "#PWR17" H 8050 2600 30  0001 C CNN
F 1 "GND" H 8050 2530 30  0001 C CNN
F 2 "" H 8050 2600 60  0000 C CNN
F 3 "" H 8050 2600 60  0000 C CNN
	1    8050 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 530CCAE9
P 8050 1700
F 0 "#PWR16" H 8050 1700 30  0001 C CNN
F 1 "GND" H 8050 1630 30  0001 C CNN
F 2 "" H 8050 1700 60  0000 C CNN
F 3 "" H 8050 1700 60  0000 C CNN
	1    8050 1700
	1    0    0    -1  
$EndComp
Text GLabel 7850 1000 0    39   Input ~ 0
Vdd
Text GLabel 7850 1900 0    39   Input ~ 0
Vdd
Text Notes 7750 800  0    60   ~ 0
connectors for SNES gamepad
Text GLabel 7850 1100 0    39   Input ~ 0
clock
Text GLabel 7850 2000 0    39   Input ~ 0
clock
Text GLabel 7850 1200 0    39   Input ~ 0
latch
Text GLabel 7850 1300 0    39   Input ~ 0
pad 1 data
Text GLabel 7850 2200 0    39   Input ~ 0
pad 2 data
Text GLabel 7850 2100 0    39   Input ~ 0
latch
Text GLabel 4850 3200 0    39   Input ~ 0
pad 2 data
Text GLabel 6350 3300 2    39   Input ~ 0
latch
Text GLabel 6350 3200 2    39   Input ~ 0
clock
Text GLabel 4850 3100 0    39   Input ~ 0
pad 1 data
$Comp
L RCA_JACK J2
U 1 1 530CD04C
P 8200 5650
F 0 "J2" H 8200 5750 60  0000 C CNN
F 1 "audio_out" V 8200 6150 60  0000 C CNN
F 2 "~" H 8200 5650 60  0000 C CNN
F 3 "~" H 8200 5650 60  0000 C CNN
	1    8200 5650
	0    1    1    0   
$EndComp
$Comp
L GND #PWR20
U 1 1 530CD057
P 8200 6250
F 0 "#PWR20" H 8200 6250 30  0001 C CNN
F 1 "GND" H 8200 6180 30  0001 C CNN
F 2 "" H 8200 6250 60  0000 C CNN
F 3 "" H 8200 6250 60  0000 C CNN
	1    8200 6250
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 530CD0AB
P 7100 5650
F 0 "R9" V 7180 5650 50  0000 C CNN
F 1 "200R" V 7100 5650 50  0000 C CNN
F 2 "" H 7100 5650 60  0000 C CNN
F 3 "" H 7100 5650 60  0000 C CNN
	1    7100 5650
	0    -1   -1   0   
$EndComp
$Comp
L C C11
U 1 1 530CD0BA
P 7350 6000
F 0 "C11" H 7400 6100 50  0000 L CNN
F 1 "100nF" H 7400 5900 50  0000 L CNN
F 2 "" H 7350 6000 60  0000 C CNN
F 3 "" H 7350 6000 60  0000 C CNN
	1    7350 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 530CD0C7
P 7350 6300
F 0 "#PWR15" H 7350 6300 30  0001 C CNN
F 1 "GND" H 7350 6230 30  0001 C CNN
F 2 "" H 7350 6300 60  0000 C CNN
F 3 "" H 7350 6300 60  0000 C CNN
	1    7350 6300
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 P2
U 1 1 530CD1CD
P 1850 3700
F 0 "P2" V 1800 3700 50  0000 C CNN
F 1 "I2C 1" V 1900 3700 50  0000 C CNN
F 2 "" H 1850 3700 60  0000 C CNN
F 3 "" H 1850 3700 60  0000 C CNN
	1    1850 3700
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR1
U 1 1 530CD1E1
P 2250 4050
F 0 "#PWR1" H 2250 4050 30  0001 C CNN
F 1 "GND" H 2250 3980 30  0001 C CNN
F 2 "" H 2250 4050 60  0000 C CNN
F 3 "" H 2250 4050 60  0000 C CNN
	1    2250 4050
	1    0    0    -1  
$EndComp
Text GLabel 2900 3700 2    39   Input ~ 0
SCL1
Text GLabel 2900 3800 2    39   Input ~ 0
SDA1
Text GLabel 2350 3600 2    39   Input ~ 0
CS1
$Comp
L R R1
U 1 1 530CD38F
P 2550 3400
F 0 "R1" V 2630 3400 50  0000 C CNN
F 1 "10k" V 2550 3400 50  0000 C CNN
F 2 "" H 2550 3400 60  0000 C CNN
F 3 "" H 2550 3400 60  0000 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 530CD39C
P 2750 3400
F 0 "R3" V 2830 3400 50  0000 C CNN
F 1 "10k" V 2750 3400 50  0000 C CNN
F 2 "" H 2750 3400 60  0000 C CNN
F 3 "" H 2750 3400 60  0000 C CNN
	1    2750 3400
	1    0    0    -1  
$EndComp
Text GLabel 2650 3050 1    39   Input ~ 0
Vdd
$Comp
L CONN_5 P3
U 1 1 530CD79F
P 1850 4950
F 0 "P3" V 1800 4950 50  0000 C CNN
F 1 "I2C 2" V 1900 4950 50  0000 C CNN
F 2 "" H 1850 4950 60  0000 C CNN
F 3 "" H 1850 4950 60  0000 C CNN
	1    1850 4950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR2
U 1 1 530CD7A5
P 2250 5300
F 0 "#PWR2" H 2250 5300 30  0001 C CNN
F 1 "GND" H 2250 5230 30  0001 C CNN
F 2 "" H 2250 5300 60  0000 C CNN
F 3 "" H 2250 5300 60  0000 C CNN
	1    2250 5300
	1    0    0    -1  
$EndComp
Text GLabel 2900 4950 2    39   Input ~ 0
SCL2
Text GLabel 2900 5050 2    39   Input ~ 0
SDA2
Text GLabel 2350 4850 2    39   Input ~ 0
CS2
$Comp
L R R2
U 1 1 530CD7B3
P 2550 4650
F 0 "R2" V 2630 4650 50  0000 C CNN
F 1 "10k" V 2550 4650 50  0000 C CNN
F 2 "" H 2550 4650 60  0000 C CNN
F 3 "" H 2550 4650 60  0000 C CNN
	1    2550 4650
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 530CD7B9
P 2750 4650
F 0 "R4" V 2830 4650 50  0000 C CNN
F 1 "10k" V 2750 4650 50  0000 C CNN
F 2 "" H 2750 4650 60  0000 C CNN
F 3 "" H 2750 4650 60  0000 C CNN
	1    2750 4650
	1    0    0    -1  
$EndComp
Text GLabel 2650 4300 1    39   Input ~ 0
Vdd
Text GLabel 4800 3600 0    39   Input ~ 0
SCL2
Text GLabel 4800 3500 0    39   Input ~ 0
SDA2
Text Notes 9350 5050 0    59   ~ 0
NOTES:\nPIN 14 OC2    video sync\nPIN 15 SDO1  video data\nPIN 16 OC1    audio PWM\n
Text GLabel 6300 4100 2    39   Input ~ 0
SCL1
Text GLabel 6300 4000 2    39   Input ~ 0
SDA1
Text GLabel 4800 4000 0    39   Input ~ 0
CS2
Text GLabel 4800 4100 0    39   Input ~ 0
CS1
$Comp
L CONN_6 P6
U 1 1 530CF1D0
P 8450 3400
F 0 "P6" V 8400 3400 60  0000 C CNN
F 1 "spare I/O" V 8500 3400 60  0000 C CNN
F 2 "" H 8450 3400 60  0000 C CNN
F 3 "" H 8450 3400 60  0000 C CNN
	1    8450 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 530CF1DF
P 8100 3800
F 0 "#PWR18" H 8100 3800 30  0001 C CNN
F 1 "GND" H 8100 3730 30  0001 C CNN
F 2 "" H 8100 3800 60  0000 C CNN
F 3 "" H 8100 3800 60  0000 C CNN
	1    8100 3800
	1    0    0    -1  
$EndComp
Text GLabel 8100 3050 1    60   Input ~ 0
Vdd
$Comp
L GND #PWR3
U 1 1 530CF4DA
P 2300 6550
F 0 "#PWR3" H 2300 6550 30  0001 C CNN
F 1 "GND" H 2300 6480 30  0001 C CNN
F 2 "" H 2300 6550 60  0000 C CNN
F 3 "" H 2300 6550 60  0000 C CNN
	1    2300 6550
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 530CF5EE
P 2000 6200
F 0 "CON1" H 2000 6450 60  0000 C CNN
F 1 "Power input" H 2000 6000 60  0000 C CNN
F 2 "" H 2000 6200 60  0000 C CNN
F 3 "" H 2000 6200 60  0000 C CNN
	1    2000 6200
	1    0    0    -1  
$EndComp
Text Notes 1100 6150 0    59   ~ 0
5 to 9 VDC
$Comp
L UA78M33 U1
U 1 1 530CF60C
P 3850 6300
F 0 "U1" H 3850 6600 60  0000 C CNN
F 1 "UA78M33" H 3850 6500 60  0000 C CNN
F 2 "~" H 3850 6300 60  0000 C CNN
F 3 "~" H 3850 6300 60  0000 C CNN
	1    3850 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 530CF6A6
P 3850 6800
F 0 "#PWR5" H 3850 6800 30  0001 C CNN
F 1 "GND" H 3850 6730 30  0001 C CNN
F 2 "" H 3850 6800 60  0000 C CNN
F 3 "" H 3850 6800 60  0000 C CNN
	1    3850 6800
	1    0    0    -1  
$EndComp
Text GLabel 4550 6250 2    60   Input ~ 0
Vdd
Text Notes 8200 7400 0    98   ~ 0
PICvision\n
$Comp
L R R5
U 1 1 530CF92E
P 4450 6550
F 0 "R5" V 4530 6550 50  0000 C CNN
F 1 "R" V 4450 6550 50  0000 C CNN
F 2 "" H 4450 6550 60  0000 C CNN
F 3 "" H 4450 6550 60  0000 C CNN
	1    4450 6550
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 530CF93D
P 4450 7050
F 0 "D1" H 4450 7150 50  0000 C CNN
F 1 "Power LED" V 4450 6750 50  0000 C CNN
F 2 "" H 4450 7050 60  0000 C CNN
F 3 "" H 4450 7050 60  0000 C CNN
	1    4450 7050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR9
U 1 1 530CF94A
P 4450 7350
F 0 "#PWR9" H 4450 7350 30  0001 C CNN
F 1 "GND" H 4450 7280 30  0001 C CNN
F 2 "" H 4450 7350 60  0000 C CNN
F 3 "" H 4450 7350 60  0000 C CNN
	1    4450 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3800 4350 3800
Wire Wire Line
	4350 3800 4350 3600
Wire Wire Line
	4350 3600 4000 3600
Wire Wire Line
	4900 3900 4350 3900
Wire Wire Line
	4350 3900 4350 4200
Wire Wire Line
	4350 4200 4000 4200
Wire Wire Line
	4000 4600 4000 4750
Wire Wire Line
	4000 3200 4000 3050
Wire Wire Line
	6250 3900 6650 3900
Wire Wire Line
	6650 3900 6650 4000
Wire Wire Line
	6250 3100 7000 3100
Wire Wire Line
	6650 3100 6650 3200
Wire Wire Line
	6250 3000 6250 2650
Connection ~ 6650 3100
Wire Wire Line
	6250 2700 7000 2700
Connection ~ 6250 2700
Connection ~ 6650 2700
Wire Wire Line
	4450 3700 4900 3700
Wire Wire Line
	4450 3700 4450 3150
Wire Wire Line
	4450 3150 4000 3150
Connection ~ 4000 3150
Wire Wire Line
	4900 4200 4650 4200
Wire Wire Line
	4500 5050 4500 5150
Connection ~ 4500 5050
Connection ~ 4500 4650
Wire Wire Line
	4500 5050 4850 5050
Wire Wire Line
	4500 4650 4850 4650
Wire Wire Line
	4700 4200 4700 4650
Connection ~ 4700 4650
Connection ~ 4700 4200
Wire Wire Line
	6250 3800 7300 3800
Wire Wire Line
	6900 4200 6900 4300
Connection ~ 6900 3800
Wire Wire Line
	7300 4200 6900 4200
Wire Wire Line
	4250 2300 4250 2650
Wire Wire Line
	4700 1300 4700 1450
Wire Wire Line
	4700 1950 4700 2100
Wire Wire Line
	4450 2100 4900 2100
Wire Wire Line
	4700 2500 4250 2500
Connection ~ 4250 2500
Wire Wire Line
	4900 3000 4900 2900
Wire Wire Line
	4900 2100 4900 2400
Connection ~ 4700 2100
Wire Wire Line
	4900 3000 4750 3000
Wire Wire Line
	4900 3300 4800 3300
Wire Wire Line
	4900 3400 4800 3400
Wire Wire Line
	2250 2150 2400 2150
Wire Wire Line
	2250 2250 2400 2250
Wire Wire Line
	2250 2450 2400 2450
Wire Wire Line
	2250 2550 2400 2550
Wire Wire Line
	2250 2350 2700 2350
Wire Wire Line
	2700 2350 2700 2400
Wire Wire Line
	7600 4700 7600 4950
Wire Wire Line
	7600 4700 7700 4700
Wire Wire Line
	7100 4700 7000 4700
Wire Wire Line
	6600 4700 6600 4200
Wire Wire Line
	6600 4200 6250 4200
Wire Wire Line
	7100 4950 6250 4950
Wire Wire Line
	6250 4950 6250 4300
Wire Wire Line
	8200 5050 8200 5250
Wire Wire Line
	8050 1600 8050 1700
Wire Wire Line
	8050 2500 8050 2600
Wire Wire Line
	7850 1900 8050 1900
Wire Wire Line
	7850 1000 8050 1000
Wire Wire Line
	7850 1100 8050 1100
Wire Wire Line
	7850 2000 8050 2000
Wire Wire Line
	7850 1200 8050 1200
Wire Wire Line
	7850 1300 8050 1300
Wire Wire Line
	7850 2100 8050 2100
Wire Wire Line
	7850 2200 8050 2200
Wire Wire Line
	7850 2300 8050 2300
Wire Wire Line
	8200 6000 8200 6250
Wire Wire Line
	7350 6200 7350 6300
Wire Wire Line
	7350 5650 7350 5800
Wire Wire Line
	7350 5650 7700 5650
Wire Wire Line
	2250 3150 2250 3500
Wire Wire Line
	2250 3600 2350 3600
Wire Wire Line
	2250 3700 2900 3700
Wire Wire Line
	2250 3800 2900 3800
Wire Wire Line
	2250 3900 2250 4050
Wire Wire Line
	2550 3650 2550 3700
Connection ~ 2550 3700
Wire Wire Line
	2250 3150 2750 3150
Wire Wire Line
	2750 3650 2750 3800
Connection ~ 2750 3800
Wire Wire Line
	2650 3150 2650 3050
Connection ~ 2650 3150
Connection ~ 2550 3150
Wire Wire Line
	2250 4400 2250 4750
Wire Wire Line
	2250 4850 2350 4850
Wire Wire Line
	2250 4950 2900 4950
Wire Wire Line
	2250 5050 2900 5050
Wire Wire Line
	2250 5150 2250 5300
Wire Wire Line
	2550 4900 2550 4950
Connection ~ 2550 4950
Wire Wire Line
	2250 4400 2750 4400
Wire Wire Line
	2750 4900 2750 5050
Connection ~ 2750 5050
Wire Wire Line
	2650 4400 2650 4300
Connection ~ 2650 4400
Connection ~ 2550 4400
Wire Wire Line
	4800 3500 4900 3500
Wire Wire Line
	4800 3600 4900 3600
Wire Wire Line
	4900 4300 4900 4500
Wire Wire Line
	4900 4500 5250 4500
Wire Wire Line
	5250 4500 5250 5650
Wire Wire Line
	6250 3200 6350 3200
Wire Wire Line
	6250 3300 6350 3300
Wire Wire Line
	4850 3100 4900 3100
Wire Wire Line
	4850 3200 4900 3200
Wire Wire Line
	4800 4000 4900 4000
Wire Wire Line
	4800 4100 4900 4100
Wire Wire Line
	6250 4000 6300 4000
Wire Wire Line
	6250 4100 6300 4100
Wire Wire Line
	8100 3650 8100 3800
Wire Wire Line
	8100 3050 8100 3150
Wire Wire Line
	6250 3700 7900 3700
Wire Wire Line
	7900 3700 7900 3550
Wire Wire Line
	7900 3550 8100 3550
Wire Wire Line
	6250 3600 7800 3600
Wire Wire Line
	7800 3600 7800 3450
Wire Wire Line
	7800 3450 8100 3450
Wire Wire Line
	6250 3500 7700 3500
Wire Wire Line
	7700 3500 7700 3350
Wire Wire Line
	7700 3350 8100 3350
Wire Wire Line
	6250 3400 7600 3400
Wire Wire Line
	7600 3400 7600 3250
Wire Wire Line
	7600 3250 8100 3250
Wire Wire Line
	2300 6300 2300 6550
Wire Wire Line
	3850 6700 3850 6800
Wire Wire Line
	4350 6250 4550 6250
Wire Wire Line
	4450 7250 4450 7350
Wire Wire Line
	4450 6800 4450 6850
Wire Wire Line
	4450 6250 4450 6300
Connection ~ 4450 6250
$Comp
L SPST SW1
U 1 1 530CFF0A
P 2850 6100
F 0 "SW1" H 2850 6200 39  0000 C CNN
F 1 "SPST" H 2850 6000 70  0000 C CNN
F 2 "" H 2850 6100 60  0000 C CNN
F 3 "" H 2850 6100 60  0000 C CNN
	1    2850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 6100 2350 6100
Wire Wire Line
	3350 6100 3350 6250
$Comp
L R R8
U 1 1 530D024B
P 6300 5650
F 0 "R8" V 6380 5650 50  0000 C CNN
F 1 "200R" V 6300 5650 50  0000 C CNN
F 2 "" H 6300 5650 60  0000 C CNN
F 3 "" H 6300 5650 60  0000 C CNN
	1    6300 5650
	0    -1   -1   0   
$EndComp
$Comp
L C C7
U 1 1 530D0251
P 6700 5950
F 0 "C7" H 6750 6050 50  0000 L CNN
F 1 "47nF" H 6750 5850 50  0000 L CNN
F 2 "" H 6700 5950 60  0000 C CNN
F 3 "" H 6700 5950 60  0000 C CNN
	1    6700 5950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 530D0257
P 6700 6300
F 0 "#PWR13" H 6700 6300 30  0001 C CNN
F 1 "GND" H 6700 6230 30  0001 C CNN
F 2 "" H 6700 6300 60  0000 C CNN
F 3 "" H 6700 6300 60  0000 C CNN
	1    6700 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5650 6850 5650
Wire Wire Line
	6700 5650 6700 5750
Connection ~ 6700 5650
Wire Wire Line
	6700 6150 6700 6300
Wire Wire Line
	5250 5650 6050 5650
$EndSCHEMATC
