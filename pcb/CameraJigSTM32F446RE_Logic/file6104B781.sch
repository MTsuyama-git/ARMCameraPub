EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+3.3V #PWR095
U 1 1 6104D2EF
P 2400 1150
F 0 "#PWR095" H 2400 1000 50  0001 C CNN
F 1 "+3.3V" H 2415 1323 50  0000 C CNN
F 2 "" H 2400 1150 50  0001 C CNN
F 3 "" H 2400 1150 50  0001 C CNN
	1    2400 1150
	1    0    0    -1  
$EndComp
Text GLabel 3150 1150 0    50   Input ~ 0
SD_NSS
Text GLabel 3150 1250 0    50   Input ~ 0
SPI2_MOSI
Text GLabel 3150 1450 0    50   Input ~ 0
SPI2_SCK
Text GLabel 3150 1650 0    50   Input ~ 0
SPI2_MISO
NoConn ~ 3150 1750
NoConn ~ 3150 1850
NoConn ~ 3150 1050
Wire Wire Line
	3150 1350 2400 1350
Wire Wire Line
	2400 1350 2400 1150
$Comp
L power:GND #PWR096
U 1 1 6104E20D
P 2400 1900
F 0 "#PWR096" H 2400 1650 50  0001 C CNN
F 1 "GND" H 2405 1727 50  0000 C CNN
F 2 "" H 2400 1900 50  0001 C CNN
F 3 "" H 2400 1900 50  0001 C CNN
	1    2400 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1550 3150 1550
$Comp
L Device:C C18
U 1 1 6104E550
P 2200 1500
F 0 "C18" H 2315 1546 50  0000 L CNN
F 1 "C" H 2315 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2238 1350 50  0001 C CNN
F 3 "~" H 2200 1500 50  0001 C CNN
	1    2200 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1350 2400 1350
Connection ~ 2400 1350
Wire Wire Line
	2200 1650 2200 1900
Wire Wire Line
	2200 1900 2400 1900
Wire Wire Line
	2400 1550 2400 1900
Connection ~ 2400 1900
$Comp
L Connector:Conn_01x06_Female J14
U 1 1 61051034
P 900 1450
F 0 "J14" H 792 1835 50  0000 C CNN
F 1 "Conn_01x06_Female" H 792 1744 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 900 1450 50  0001 C CNN
F 3 "~" H 900 1450 50  0001 C CNN
	1    900  1450
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR091
U 1 1 61051824
P 1400 1250
F 0 "#PWR091" H 1400 1100 50  0001 C CNN
F 1 "+3.3V" H 1415 1423 50  0000 C CNN
F 2 "" H 1400 1250 50  0001 C CNN
F 3 "" H 1400 1250 50  0001 C CNN
	1    1400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1250 1100 1250
$Comp
L power:GND #PWR093
U 1 1 61052065
P 1600 1350
F 0 "#PWR093" H 1600 1100 50  0001 C CNN
F 1 "GND" H 1605 1177 50  0000 C CNN
F 2 "" H 1600 1350 50  0001 C CNN
F 3 "" H 1600 1350 50  0001 C CNN
	1    1600 1350
	1    0    0    -1  
$EndComp
Text GLabel 1100 1450 2    50   Output ~ 0
SD_NSS
Wire Wire Line
	1100 1350 1600 1350
Text GLabel 1100 1550 2    50   Output ~ 0
SPI2_MOSI
Text GLabel 1100 1650 2    50   Output ~ 0
SPI2_SCK
Text GLabel 1100 1750 2    50   Output ~ 0
SPI2_MISO
Text Notes 1400 1950 2    50   ~ 0
main board
$Comp
L Connector:Conn_01x06_Female J15
U 1 1 61054E47
P 900 2550
F 0 "J15" H 792 2935 50  0000 C CNN
F 1 "Conn_01x06_Female" H 792 2844 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 900 2550 50  0001 C CNN
F 3 "~" H 900 2550 50  0001 C CNN
	1    900  2550
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR092
U 1 1 61054E4D
P 1400 2350
F 0 "#PWR092" H 1400 2200 50  0001 C CNN
F 1 "+3.3V" H 1415 2523 50  0000 C CNN
F 2 "" H 1400 2350 50  0001 C CNN
F 3 "" H 1400 2350 50  0001 C CNN
	1    1400 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2350 1100 2350
$Comp
L power:GND #PWR094
U 1 1 61054E54
P 1600 2450
F 0 "#PWR094" H 1600 2200 50  0001 C CNN
F 1 "GND" H 1605 2277 50  0000 C CNN
F 2 "" H 1600 2450 50  0001 C CNN
F 3 "" H 1600 2450 50  0001 C CNN
	1    1600 2450
	1    0    0    -1  
$EndComp
Text GLabel 1100 2550 2    50   Output ~ 0
SD_NSS
Wire Wire Line
	1100 2450 1600 2450
Text GLabel 1100 2650 2    50   Output ~ 0
SPI2_MOSI
Text GLabel 1100 2750 2    50   Output ~ 0
SPI2_SCK
Text GLabel 1100 2850 2    50   Output ~ 0
SPI2_MISO
Text Notes 1400 3050 2    50   ~ 0
sd board
$Comp
L Connector:Micro_SD_Card_Det_Hirose_DM3AT J16
U 1 1 6174B216
P 4050 1450
F 0 "J16" H 4000 2267 50  0000 C CNN
F 1 "Micro_SD_Card_Det_Hirose_DM3AT" H 4000 2176 50  0000 C CNN
F 2 "" H 6100 2150 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 4050 1550 50  0001 C CNN
	1    4050 1450
	1    0    0    -1  
$EndComp
NoConn ~ 3150 1950
NoConn ~ 4850 1950
$EndSCHEMATC
