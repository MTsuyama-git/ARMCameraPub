EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L jig:SOT-89 U?
U 1 1 60F6B009
P 1650 1100
AR Path="/60F6B009" Ref="U?"  Part="1" 
AR Path="/60F5F3E4/60F6B009" Ref="U4"  Part="1" 
F 0 "U4" V 1638 972 50  0000 R CNN
F 1 "SOT-89" V 1547 972 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 1650 1100 50  0001 C CNN
F 3 "" H 1650 1100 50  0001 C CNN
	1    1650 1100
	0    -1   -1   0   
$EndComp
$Comp
L jig:SOT-89 U?
U 1 1 60F6B00F
P 2550 1100
AR Path="/60F6B00F" Ref="U?"  Part="1" 
AR Path="/60F5F3E4/60F6B00F" Ref="U6"  Part="1" 
F 0 "U6" V 2538 972 50  0000 R CNN
F 1 "SOT-89" V 2447 972 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 2550 1100 50  0001 C CNN
F 3 "" H 2550 1100 50  0001 C CNN
	1    2550 1100
	0    -1   -1   0   
$EndComp
$Comp
L power:+8V #PWR?
U 1 1 60F6B015
P 1200 1400
AR Path="/60F6B015" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F6B015" Ref="#PWR063"  Part="1" 
F 0 "#PWR063" H 1200 1250 50  0001 C CNN
F 1 "+8V" H 1215 1573 50  0000 C CNN
F 2 "" H 1200 1400 50  0001 C CNN
F 3 "" H 1200 1400 50  0001 C CNN
	1    1200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 1400 1350 1400
$Comp
L Device:C C?
U 1 1 60F6B01C
P 1350 1550
AR Path="/60F6B01C" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F6B01C" Ref="C9"  Part="1" 
F 0 "C9" H 1465 1596 50  0000 L CNN
F 1 "C" H 1465 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1388 1400 50  0001 C CNN
F 3 "~" H 1350 1550 50  0001 C CNN
	1    1350 1550
	1    0    0    -1  
$EndComp
Connection ~ 1350 1400
Wire Wire Line
	1350 1400 1500 1400
$Comp
L Device:C C?
U 1 1 60F6B024
P 1800 1550
AR Path="/60F6B024" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F6B024" Ref="C11"  Part="1" 
F 0 "C11" H 1915 1596 50  0000 L CNN
F 1 "C" H 1915 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1838 1400 50  0001 C CNN
F 3 "~" H 1800 1550 50  0001 C CNN
	1    1800 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F6B02A
P 1600 1700
AR Path="/60F6B02A" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F6B02A" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 1600 1450 50  0001 C CNN
F 1 "GND" H 1605 1527 50  0000 C CNN
F 2 "" H 1600 1700 50  0001 C CNN
F 3 "" H 1600 1700 50  0001 C CNN
	1    1600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1700 1600 1700
Connection ~ 1600 1700
Wire Wire Line
	1600 1700 1350 1700
Wire Wire Line
	1600 1400 1600 1700
$Comp
L power:+5V #PWR?
U 1 1 60F6B034
P 1950 1400
AR Path="/60F6B034" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F6B034" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 1950 1250 50  0001 C CNN
F 1 "+5V" H 1965 1573 50  0000 C CNN
F 2 "" H 1950 1400 50  0001 C CNN
F 3 "" H 1950 1400 50  0001 C CNN
	1    1950 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1400 1800 1400
Connection ~ 1800 1400
Wire Wire Line
	1800 1400 1950 1400
Wire Wire Line
	1950 1400 2200 1400
Connection ~ 1950 1400
$Comp
L Device:C C?
U 1 1 60F6B03F
P 2200 1550
AR Path="/60F6B03F" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F6B03F" Ref="C14"  Part="1" 
F 0 "C14" H 2315 1596 50  0000 L CNN
F 1 "C" H 2315 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2238 1400 50  0001 C CNN
F 3 "~" H 2200 1550 50  0001 C CNN
	1    2200 1550
	1    0    0    -1  
$EndComp
Connection ~ 2200 1400
Wire Wire Line
	2200 1400 2400 1400
$Comp
L power:GND #PWR?
U 1 1 60F6B047
P 2500 1700
AR Path="/60F6B047" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F6B047" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 2500 1450 50  0001 C CNN
F 1 "GND" H 2505 1527 50  0000 C CNN
F 2 "" H 2500 1700 50  0001 C CNN
F 3 "" H 2500 1700 50  0001 C CNN
	1    2500 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60F6B04D
P 2750 1550
AR Path="/60F6B04D" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F6B04D" Ref="C15"  Part="1" 
F 0 "C15" H 2865 1596 50  0000 L CNN
F 1 "C" H 2865 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2788 1400 50  0001 C CNN
F 3 "~" H 2750 1550 50  0001 C CNN
	1    2750 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1400 2750 1400
Wire Wire Line
	2750 1700 2500 1700
Connection ~ 2500 1700
Wire Wire Line
	2500 1700 2200 1700
Wire Wire Line
	2500 1400 2500 1700
Wire Wire Line
	2750 1400 3000 1400
Connection ~ 2750 1400
$Comp
L power:+3.3V #PWR?
U 1 1 60F6B05A
P 3000 1400
AR Path="/60F6B05A" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F6B05A" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 3000 1250 50  0001 C CNN
F 1 "+3.3V" H 3015 1573 50  0000 C CNN
F 2 "" H 3000 1400 50  0001 C CNN
F 3 "" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L jig:MP2307 U?
U 1 1 60F73EFC
P 1800 3250
AR Path="/60F73EFC" Ref="U?"  Part="1" 
AR Path="/60F5F3E4/60F73EFC" Ref="U5"  Part="1" 
F 0 "U5" H 1675 3565 50  0000 C CNN
F 1 "MP2307" H 1675 3474 50  0000 C CNN
F 2 "Package_SO:HSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.1mm_ThermalVias" H 1800 3250 50  0001 C CNN
F 3 "" H 1800 3250 50  0001 C CNN
	1    1800 3250
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 60F73F02
P 2000 2700
AR Path="/60F73F02" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F02" Ref="C13"  Part="1" 
F 0 "C13" V 1748 2700 50  0000 C CNN
F 1 "C" V 1839 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2038 2550 50  0001 C CNN
F 3 "~" H 2000 2700 50  0001 C CNN
	1    2000 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 2700 1850 2800
$Comp
L power:+9V #PWR?
U 1 1 60F73F09
P 1050 2650
AR Path="/60F73F09" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F09" Ref="#PWR061"  Part="1" 
F 0 "#PWR061" H 1050 2500 50  0001 C CNN
F 1 "+9V" H 1065 2823 50  0000 C CNN
F 2 "" H 1050 2650 50  0001 C CNN
F 3 "" H 1050 2650 50  0001 C CNN
	1    1050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2650 1250 2650
Wire Wire Line
	1750 2650 1750 2800
Wire Wire Line
	1650 2800 1650 2400
Wire Wire Line
	1650 2400 2150 2400
Wire Wire Line
	2150 2400 2150 2700
$Comp
L power:GND #PWR?
U 1 1 60F73F14
P 1400 2800
AR Path="/60F73F14" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F14" Ref="#PWR064"  Part="1" 
F 0 "#PWR064" H 1400 2550 50  0001 C CNN
F 1 "GND" H 1405 2627 50  0000 C CNN
F 2 "" H 1400 2800 50  0001 C CNN
F 3 "" H 1400 2800 50  0001 C CNN
	1    1400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2800 1550 2800
$Comp
L Device:R R?
U 1 1 60F73F1B
P 1250 2800
AR Path="/60F73F1B" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F1B" Ref="R32"  Part="1" 
F 0 "R32" H 1320 2846 50  0000 L CNN
F 1 "R" H 1320 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1180 2800 50  0001 C CNN
F 3 "~" H 1250 2800 50  0001 C CNN
	1    1250 2800
	1    0    0    -1  
$EndComp
Connection ~ 1250 2650
Wire Wire Line
	1250 2650 1750 2650
Wire Wire Line
	1750 3450 1750 3650
Wire Wire Line
	1750 3650 1250 3650
Wire Wire Line
	1250 3650 1250 2950
$Comp
L Device:C C?
U 1 1 60F73F26
P 1050 2800
AR Path="/60F73F26" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F26" Ref="C7"  Part="1" 
F 0 "C7" H 1165 2846 50  0000 L CNN
F 1 "C" H 1165 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1088 2650 50  0001 C CNN
F 3 "~" H 1050 2800 50  0001 C CNN
	1    1050 2800
	1    0    0    -1  
$EndComp
Connection ~ 1050 2650
$Comp
L Device:C C?
U 1 1 60F73F2D
P 1050 3100
AR Path="/60F73F2D" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F2D" Ref="C8"  Part="1" 
F 0 "C8" H 1165 3146 50  0000 L CNN
F 1 "C" H 1165 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1088 2950 50  0001 C CNN
F 3 "~" H 1050 3100 50  0001 C CNN
	1    1050 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F73F33
P 1050 3250
AR Path="/60F73F33" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F33" Ref="#PWR062"  Part="1" 
F 0 "#PWR062" H 1050 3000 50  0001 C CNN
F 1 "GND" H 1055 3077 50  0000 C CNN
F 2 "" H 1050 3250 50  0001 C CNN
F 3 "" H 1050 3250 50  0001 C CNN
	1    1050 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60F73F39
P 1650 3900
AR Path="/60F73F39" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F39" Ref="C10"  Part="1" 
F 0 "C10" H 1765 3946 50  0000 L CNN
F 1 "C" H 1765 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 3750 50  0001 C CNN
F 3 "~" H 1650 3900 50  0001 C CNN
	1    1650 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3450 1650 3750
$Comp
L Device:R R?
U 1 1 60F73F40
P 1650 4200
AR Path="/60F73F40" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F40" Ref="R33"  Part="1" 
F 0 "R33" H 1720 4246 50  0000 L CNN
F 1 "R" H 1720 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1580 4200 50  0001 C CNN
F 3 "~" H 1650 4200 50  0001 C CNN
	1    1650 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F73F46
P 1650 4350
AR Path="/60F73F46" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F46" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 1650 4100 50  0001 C CNN
F 1 "GND" H 1655 4177 50  0000 C CNN
F 2 "" H 1650 4350 50  0001 C CNN
F 3 "" H 1650 4350 50  0001 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F73F4C
P 2300 3700
AR Path="/60F73F4C" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F4C" Ref="R34"  Part="1" 
F 0 "R34" H 2370 3746 50  0000 L CNN
F 1 "R" H 2370 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2230 3700 50  0001 C CNN
F 3 "~" H 2300 3700 50  0001 C CNN
	1    2300 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60F73F52
P 1950 3900
AR Path="/60F73F52" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F52" Ref="C12"  Part="1" 
F 0 "C12" H 2065 3946 50  0000 L CNN
F 1 "C" H 2065 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1988 3750 50  0001 C CNN
F 3 "~" H 1950 3900 50  0001 C CNN
	1    1950 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3450 1850 3750
Wire Wire Line
	1850 3750 1950 3750
Wire Wire Line
	1950 4050 1950 4350
Wire Wire Line
	1950 4350 1650 4350
Connection ~ 1650 4350
Wire Wire Line
	1550 3450 1550 3550
$Comp
L power:GND #PWR?
U 1 1 60F73F5E
P 2300 3850
AR Path="/60F73F5E" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F5E" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 2300 3600 50  0001 C CNN
F 1 "GND" H 2305 3677 50  0000 C CNN
F 2 "" H 2300 3850 50  0001 C CNN
F 3 "" H 2300 3850 50  0001 C CNN
	1    2300 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F73F64
P 2450 3550
AR Path="/60F73F64" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F64" Ref="R35"  Part="1" 
F 0 "R35" V 2243 3550 50  0000 C CNN
F 1 "R" V 2334 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2380 3550 50  0001 C CNN
F 3 "~" H 2450 3550 50  0001 C CNN
	1    2450 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F73F6A
P 2750 3550
AR Path="/60F73F6A" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F6A" Ref="R36"  Part="1" 
F 0 "R36" V 2543 3550 50  0000 C CNN
F 1 "R" V 2634 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2680 3550 50  0001 C CNN
F 3 "~" H 2750 3550 50  0001 C CNN
	1    2750 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F73F70
P 3050 3550
AR Path="/60F73F70" Ref="R?"  Part="1" 
AR Path="/60F5F3E4/60F73F70" Ref="R37"  Part="1" 
F 0 "R37" V 2843 3550 50  0000 C CNN
F 1 "R" V 2934 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2980 3550 50  0001 C CNN
F 3 "~" H 3050 3550 50  0001 C CNN
	1    3050 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	1550 3550 2300 3550
Connection ~ 2300 3550
$Comp
L Device:C C?
U 1 1 60F73F78
P 3200 3700
AR Path="/60F73F78" Ref="C?"  Part="1" 
AR Path="/60F5F3E4/60F73F78" Ref="C16"  Part="1" 
F 0 "C16" H 3315 3746 50  0000 L CNN
F 1 "C" H 3315 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3238 3550 50  0001 C CNN
F 3 "~" H 3200 3700 50  0001 C CNN
	1    3200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3850 2300 3850
Connection ~ 2300 3850
$Comp
L Device:L L?
U 1 1 60F73F80
P 2300 2700
AR Path="/60F73F80" Ref="L?"  Part="1" 
AR Path="/60F5F3E4/60F73F80" Ref="L1"  Part="1" 
F 0 "L1" V 2490 2700 50  0000 C CNN
F 1 "L" V 2399 2700 50  0000 C CNN
F 2 "thermal_printer_head_jig_k8:inductor_NR10050T100M" H 2300 2700 50  0001 C CNN
F 3 "~" H 2300 2700 50  0001 C CNN
	1    2300 2700
	0    -1   -1   0   
$EndComp
Connection ~ 2150 2700
Wire Wire Line
	2450 2700 3200 2700
Wire Wire Line
	3200 2700 3200 3550
Connection ~ 3200 3550
$Comp
L power:+8V #PWR?
U 1 1 60F73F8A
P 3200 2700
AR Path="/60F73F8A" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F73F8A" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 3200 2550 50  0001 C CNN
F 1 "+8V" H 3215 2873 50  0000 C CNN
F 2 "" H 3200 2700 50  0001 C CNN
F 3 "" H 3200 2700 50  0001 C CNN
	1    3200 2700
	1    0    0    -1  
$EndComp
Connection ~ 3200 2700
$Comp
L jig:power_supply U?
U 1 1 60F7E279
P 1300 5500
AR Path="/60F7E279" Ref="U?"  Part="1" 
AR Path="/60F5F3E4/60F7E279" Ref="U3"  Part="1" 
F 0 "U3" H 1142 5925 50  0000 C CNN
F 1 "power_supply" H 1142 5834 50  0000 C CNN
F 2 "thermal_printer_head_jig_k8:POWER_Supply" H 850 5550 50  0001 C CNN
F 3 "" H 850 5550 50  0001 C CNN
	1    1300 5500
	-1   0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x01 SW?
U 1 1 60F7E27F
P 2150 5300
AR Path="/60F7E27F" Ref="SW?"  Part="1" 
AR Path="/60F5F3E4/60F7E27F" Ref="SW6"  Part="1" 
F 0 "SW6" H 2150 5567 50  0000 C CNN
F 1 "SW_DIP_x01" H 2150 5476 50  0000 C CNN
F 2 "thermal_printer_head_jig_k8:SW_2WAY" H 2150 5300 50  0001 C CNN
F 3 "~" H 2150 5300 50  0001 C CNN
	1    2150 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 60F7E285
P 2450 5300
AR Path="/60F7E285" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F7E285" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 2450 5150 50  0001 C CNN
F 1 "+9V" H 2465 5473 50  0000 C CNN
F 2 "" H 2450 5300 50  0001 C CNN
F 3 "" H 2450 5300 50  0001 C CNN
	1    2450 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F7E28B
P 1850 5400
AR Path="/60F7E28B" Ref="#PWR?"  Part="1" 
AR Path="/60F5F3E4/60F7E28B" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 1850 5150 50  0001 C CNN
F 1 "GND" H 1855 5227 50  0000 C CNN
F 2 "" H 1850 5400 50  0001 C CNN
F 3 "" H 1850 5400 50  0001 C CNN
	1    1850 5400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J8
U 1 1 60F8DBFC
P 4100 2000
F 0 "J8" H 4128 1976 50  0000 L CNN
F 1 "Conn_01x05" H 4128 1885 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4100 2000 50  0001 C CNN
F 3 "~" H 4100 2000 50  0001 C CNN
	1    4100 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+8V #PWR077
U 1 1 60F8FE7B
P 3900 1900
F 0 "#PWR077" H 3900 1750 50  0001 C CNN
F 1 "+8V" H 3915 2073 50  0000 C CNN
F 2 "" H 3900 1900 50  0001 C CNN
F 3 "" H 3900 1900 50  0001 C CNN
	1    3900 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR076
U 1 1 60F90A38
P 3750 2000
F 0 "#PWR076" H 3750 1850 50  0001 C CNN
F 1 "+5V" H 3765 2173 50  0000 C CNN
F 2 "" H 3750 2000 50  0001 C CNN
F 3 "" H 3750 2000 50  0001 C CNN
	1    3750 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2000 3750 2000
$Comp
L power:+3.3V #PWR074
U 1 1 60F96086
P 3650 2100
F 0 "#PWR074" H 3650 1950 50  0001 C CNN
F 1 "+3.3V" H 3665 2273 50  0000 C CNN
F 2 "" H 3650 2100 50  0001 C CNN
F 3 "" H 3650 2100 50  0001 C CNN
	1    3650 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2100 3900 2100
$Comp
L power:GND #PWR075
U 1 1 60F9712E
P 3700 2200
F 0 "#PWR075" H 3700 1950 50  0001 C CNN
F 1 "GND" H 3705 2027 50  0000 C CNN
F 2 "" H 3700 2200 50  0001 C CNN
F 3 "" H 3700 2200 50  0001 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2200 3900 2200
Text Notes 4200 2650 2    50   ~ 0
power board
$Comp
L Connector:Conn_01x04_Female J9
U 1 1 60F9CFB8
P 5200 1950
F 0 "J9" H 5228 1926 50  0000 L CNN
F 1 "Conn_01x05" H 5228 1835 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 5200 1950 50  0001 C CNN
F 3 "~" H 5200 1950 50  0001 C CNN
	1    5200 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+8V #PWR081
U 1 1 60F9CFBE
P 5000 1850
F 0 "#PWR081" H 5000 1700 50  0001 C CNN
F 1 "+8V" H 5015 2023 50  0000 C CNN
F 2 "" H 5000 1850 50  0001 C CNN
F 3 "" H 5000 1850 50  0001 C CNN
	1    5000 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR080
U 1 1 60F9CFC4
P 4850 1950
F 0 "#PWR080" H 4850 1800 50  0001 C CNN
F 1 "+5V" H 4865 2123 50  0000 C CNN
F 2 "" H 4850 1950 50  0001 C CNN
F 3 "" H 4850 1950 50  0001 C CNN
	1    4850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1950 4850 1950
$Comp
L power:+3.3V #PWR078
U 1 1 60F9CFCB
P 4750 2050
F 0 "#PWR078" H 4750 1900 50  0001 C CNN
F 1 "+3.3V" H 4765 2223 50  0000 C CNN
F 2 "" H 4750 2050 50  0001 C CNN
F 3 "" H 4750 2050 50  0001 C CNN
	1    4750 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2050 5000 2050
$Comp
L power:GND #PWR079
U 1 1 60F9CFD2
P 4800 2150
F 0 "#PWR079" H 4800 1900 50  0001 C CNN
F 1 "GND" H 4805 1977 50  0000 C CNN
F 2 "" H 4800 2150 50  0001 C CNN
F 3 "" H 4800 2150 50  0001 C CNN
	1    4800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2150 5000 2150
Text Notes 5150 2600 2    50   ~ 0
main board
$Comp
L Connector:Conn_01x04_Female J21
U 1 1 6167537F
P 6400 1900
F 0 "J21" H 6428 1876 50  0000 L CNN
F 1 "Conn_01x05" H 6428 1785 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6400 1900 50  0001 C CNN
F 3 "~" H 6400 1900 50  0001 C CNN
	1    6400 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+8V #PWR099
U 1 1 61675385
P 6200 1800
F 0 "#PWR099" H 6200 1650 50  0001 C CNN
F 1 "+8V" H 6215 1973 50  0000 C CNN
F 2 "" H 6200 1800 50  0001 C CNN
F 3 "" H 6200 1800 50  0001 C CNN
	1    6200 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR098
U 1 1 6167538B
P 6050 1900
F 0 "#PWR098" H 6050 1750 50  0001 C CNN
F 1 "+5V" H 6065 2073 50  0000 C CNN
F 2 "" H 6050 1900 50  0001 C CNN
F 3 "" H 6050 1900 50  0001 C CNN
	1    6050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1900 6050 1900
$Comp
L power:+3.3V #PWR043
U 1 1 61675392
P 5950 2000
F 0 "#PWR043" H 5950 1850 50  0001 C CNN
F 1 "+3.3V" H 5965 2173 50  0000 C CNN
F 2 "" H 5950 2000 50  0001 C CNN
F 3 "" H 5950 2000 50  0001 C CNN
	1    5950 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2000 6200 2000
$Comp
L power:GND #PWR097
U 1 1 61675399
P 6000 2100
F 0 "#PWR097" H 6000 1850 50  0001 C CNN
F 1 "GND" H 6005 1927 50  0000 C CNN
F 2 "" H 6000 2100 50  0001 C CNN
F 3 "" H 6000 2100 50  0001 C CNN
	1    6000 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2100 6200 2100
Text Notes 6350 2550 2    50   ~ 0
main board(out)
$EndSCHEMATC
