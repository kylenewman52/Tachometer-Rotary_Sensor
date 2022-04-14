# Tachometer-Rotary_Sensor
This is a simple project to calculate rpm of a wheel. This includes a lcd_lib that I used to help display the results. You simply spin the wheel encoder between the rotary sensor and it will calulate the RPM in real time. 

*Note: There are no specific requirements, so the sensor records the RPM in half second intervals. This code can be altered to improve precision.* 

The compile_script.py can be used to compile the program and the lcd library. Using the script assumes you have python installed. Changes may be necessary for the AVR-GCC path and the com port of the Ardunio. Examples for using the script can be found inside the script. Credits to Dr. Peter Jamieson for the script. 

The pin layout for the lcd can be changed in HD44780_Settings.h found in lcd_lib. The rotary sensor can only be on pin 2 or pin 3(interrupt pin 0/1 respectively) and is used on pin 2 within the code. 
