#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"
#include "myLCD.h"


int main()
{
		DDRB = 0b00100011;
		DDRD = 0xF0;
		char MyChar = 'A';
		// Initailize the LCD for 4-bit mode, two lines, and 5 x 8 characters //
		// Inits found on Page 46 of datasheet and Table 6 for function set instructions //
		LCD_init();

		// Write a single character //
		LCD_write_char(MyChar);

		// line two //
		LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
		_delay_us(80); // delay must be > 37us - datasheet forgets to mention this //
		LCD_write_char(MyChar);

		while(1)
		{
			PORTB ^= 0x20;
			_delay_ms(500);
		}

return 1;
}
























