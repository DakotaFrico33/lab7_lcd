#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"
#include "myLCD.h"
#define END_OF_LINE 15
char keyCount = 0;
	char line = 0;
	char key;
	char keyPrev;
	int lineCount = 0;



int lineChange(int c, char *l){
	if(c == END_OF_LINE)
	{
		c = 0;
		if (*l==0) //end of line, wrap to second line
		{
			LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
			_delay_us(80);
			*l = 1;
		}
		else if (*l==1) //end of line, overwrite first line
		{
			LCD_write_instruction(LCD_4bit_cursorSET|LineOneStart);
			_delay_us(80);
			*l = 0;
		}
	}
	return c;
}

void typeMsg()
{

	
	key = USARTreceive(); //type on keyboard
	USARTtransmit(key);//echo bit back to terminal
	LCD_write_char(key); // write char to LCD screen
	_delay_us(80);

	keyCount = keyCheck(key, keyPrev, keyCount, &line);
	keyPrev = key;
	keyCount++;
}

int keyCheck(unsigned char cur, unsigned char prev, char c, char *l){
	if (cur == '\t' && prev == '\t'){
		LCD_write_instruction(LCD_4bit_displayCLEAR);
		_delay_us(80);
		return lineChange(END_OF_LINE, l);
	}
	else if(cur == '\r')
		return lineChange(END_OF_LINE, l);
	return lineChange(c,l);
}


void deliverable1(char a)
{
	LCD_write_char(a);
	_delay_ms(1000);
}


void outputString(char *str)
{
	int i = 0;
	
	while (str[i]!='\0')
	{
		LCD_write_char(str[i]);
		_delay_us(80);
		i++;
	}
}

void deliverable2(char *str)
{
	LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
	_delay_us(80);
	outputString(str);
	_delay_ms(1000);
}



void clean()
{
	LCD_write_instruction(LCD_4bit_displayCLEAR);
	_delay_us(80);
	LCD_write_instruction(LCD_4bit_cursorSET|LineOneStart);
	_delay_us(80);
}



int main()
{
		DDRB = 0b00100011;
		DDRD = 0xF0;
		char myStr[100] = "Ciao";
		char MyChar = 'C';
		// Initailize the LCD for 4-bit mode, two lines, and 5 x 8 characters //
		// Inits found on Page 46 of datasheet and Table 6 for function set instructions //
		LCD_init();
		initUSART();

		// Write a single character //
		deliverable1(MyChar);

	
		LCD_init();
		// Write a string //
		deliverable2(myStr);

		LCD_init();

		while(1)
		{
			typeMsg();
		}

return 1;
}
























