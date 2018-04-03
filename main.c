#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"
#include "myLCD.h"

void outputString(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i]!='\0')
	{
		LCD_write_char(str[i]);
		i++;
		j++;
		if (j==16) //end of line, wrap to second line
		{
			LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
			_delay_us(80);
		}

		if (j==32) //end of line, overwrite first line
		{
			LCD_write_instruction(LCD_4bit_cursorSET|LineOneStart);
			_delay_ms(1000);
			j=0;
		}
		

	}
}

void typeMsg()
{
	char key;

	key = USARTreceive(); //type on keyboard
	USARTtransmit(key);//echo bit back to terminal
	_delay_us(80);
	LCD_write_char(key); // write char to LCD screen
	_delay_us(80);
}



int main()
{
		DDRB = 0b00100011;
		DDRD = 0xF0;
		char myStr[100] = "Hello!";
		char MyChar = 'C';
		// Initailize the LCD for 4-bit mode, two lines, and 5 x 8 characters //
		// Inits found on Page 46 of datasheet and Table 6 for function set instructions //
		LCD_init();
		initUSART();

		// Write a single character or a string //
		//LCD_write_char(MyChar);
		outputString(myStr);

		// line two //
		//LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
		//_delay_us(80); // delay must be > 37us - datasheet forgets to mention this //
		//LCD_write_char(MyChar);

		_delay_ms(1000);

		LCD_write_instruction(LCD_4bit_displayCLEAR);
		_delay_us(80);
		LCD_write_instruction(LCD_4bit_cursorSET|LineOneStart);
		_delay_us(80);




		while(1)
		{
			typeMsg();
		}

return 1;
}
























