#include <stdint.h>
#include "lcd_lib/hd44780.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* GLOBALS - not great */
volatile uint8_t rotationCount;

// Change based on wheel encoder
// **Note** small error based on rounding to int value
#define TicksPerRotaion 22
// Rotary encoder on external interrupt pin 0 => arduino uno pin 2
#define RotaryEncoder     D, 2	


int main(void)
{
	//Setup
	LCD_Setup();
	PinMode(RotaryEncoder, Input); 
	EICRA |= (1 << ISC01);    // Trigger on falling edge
	EIMSK |= (1 << INT0);     // Enable external interrupt INT0
	sei();                    // Enable global interrupts
	
	while (1) {
		uint8_t line;
		uint8_t rpmSpeed;
		// Reset the rotation count to avoid an overflow runtime error.
		rotationCount = 0;
		
		// Calculate the rpm 
		uint8_t tmpRotationCount = rotationCount;
		_delay_ms(500);
		uint8_t rotationChange = rotationCount - tmpRotationCount;
		// Formula to change 120x/TicksPerRotaion => rpm
		rpmSpeed = 120 * rotationChange / TicksPerRotaion;
		
		// Print Results to LCD
		for (line = 0; line < 2; line++)
		{	
			LCD_GotoXY(0, line);
			if (line == 0)
			{
				LCD_PrintString("Current RPM: ");
			}
			else 
			{	
				LCD_PrintInteger(rpmSpeed);
				LCD_PrintString("      ");
			}
		}
	};
	
	return 0;
}

// Interrupt Service Routine attached to INT0 vector
ISR(INT0_vect)
{
  rotationCount++;
}
