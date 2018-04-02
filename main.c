#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"

#define LCD_Reset				0b00110000
#define LCD_4bit_enable			0b00110000
#define LCD_4bit_mode			0b00110000
#define LCD_4bit_displayOFF		0b00001000
#define LCD_4bit_displayON		0b00001100
#define LCD_4bit_displayCLEAR	0b00000001
#define LCD_4bit_entryMODE		0b00000110
#define LCD_4bit_cursorSET		0b10000000

// For two line mode //
#define LineOneStart	0x00
#define	LineTwoStart	0x40

// Pin definitions for PORTB control lines //
#define LCD_EnablePin	1
#define LCD_RegisterSelectPin	0

// Prototypes //
void LCD_init();
void LCD_E_RS_init();
void LCD_write_4bits(uint8_t);
void LCD_EnablePulse();
void LCD_write_instruction(uint8_t);

void LCD_write_char(char);


void LCD_init()
{
	_delay_ms(100);

	LCD_E_RS_init();

	LCD_write_4bits(LCD_Reset);
	_delay_ms(10);

	LCD_write_4bits(LCD_Reset);
	_delay_us(200);

	LCD_write_4bits(LCD_Reset);
	_delay_us(200);


	LCD_write_4bits(LCD_4bit_enable);
	_delay_us(80);


	///////// system reset is complete - set up LCD modes //////////
	LCD_write_instruction(LCD_4bit_mode);
	_delay_us(80);

	LCD_write_instruction(LCD_4bit_displayOFF);
	_delay_us(80);

	LCD_write_instruction(LCD_4bit_displayCLEAR);
	_delay_ms(10);

	LCD_write_instruction(LCD_4bit_displayON);
	_delay_us(80);
}


void LCD_E_RS_init()
{
	PORTB &= ~(1<<LCD_EnablePin);
	PORTB &= ~(1<<LCD_RegisterSelectPin);
}


void LCD_write_4bits(uint8_t data)
{
	PORTD &= 0b00001111;
	PORTD |= data;

	LCD_EnablePulse();
}


void LCD_EnablePulse()
{
	//PORTB &= ~(1<<LCD_EnablePin);
	//_delay_us(1)
	PORTB |= (1<<LCD_EnablePin);
	_delay_us(1);
	PORTB &= ~(1<<LCD_EnablePin);
	_delay_us(1);
}



void LCD_write_instruction(uint8_t instruction)
{
	//PORTB &= ~(1<<LCD_RegisterSelectPin);
	LCD_E_RS_init();

	LCD_write_4bits(instruction);
	LCD_write_4bits(instruction<<4);
}



void LCD_write_char(char data)
{
	PORTB |= (1<<LCD_RegisterSelectPin);
	PORTB &= ~(1<<LCD_EnablePin);
	LCD_write_4bits(data);
	LCD_write_4bits(data<<4);
	_delay_us(80);
}

int main()
{
		DDRB = 0x23;
		DDRD = 0xF0;
		char MyChar = 'C';

		LCD_init();

		LCD_write_char(MyChar);

		LCD_write_instruction(LCD_4bit_cursorSET|LineTwoStart);
		_delay_us(80);
		LCD_write_char(MyChar);

		while(1)
		{
			PORTB ^= 0x20;
			_delay_ms(500);
		}

return 1;
}
























