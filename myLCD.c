#include <avr/io.h>
#include <util/delay.h>
#include "myLCD.h"

// Important notes in sequence from page 46 in HD44780U datasheet - initialize the LCD in 4-bit two line mode //
void LCD_init()
{
	// wait for power up - more than 40ms for vcc to rise to 2.7V //
	_delay_ms(100);

	// Note that we need to reset the controller three different times with different delay //
	LCD_E_RS_init(); // Set the E and RS pins active low for each LCD reset

	// First reset and wait more than 4.1 ms //
	LCD_write_4bits(LCD_Reset);
	_delay_ms(10);

	// Second reset and wait more than 100 us //
	LCD_write_4bits(LCD_Reset);
	_delay_us(200);

	// Third reset and wait more than 100us (not mentioned in the data sheet) //
	LCD_write_4bits(LCD_Reset);
	_delay_us(200);


	// Now we can set the LCD to 4-bit mode //
	LCD_write_4bits(LCD_4bit_enable);
	_delay_us(80); // delay must be >37us //


	///////// system reset is complete - set up LCD modes //////////
	// At this point we are operating in 4-bit mode and can now set the line numbers and fonto size //
	LCD_write_instruction(LCD_4bit_mode);
	_delay_us(80); // delay must be >37us //

	LCD_write_instruction(LCD_4bit_displayOFF);
	_delay_us(80); // delay must be >37us //

	LCD_write_instruction(LCD_4bit_displayCLEAR);
	_delay_ms(10); // delay must be >2ms //

	LCD_write_instruction(LCD_4bit_entryMODE);
	_delay_us(80); // delay must be >37us //


	// The lCD should now be initialized to operate in 4-bit mode, 2 lines, 5 x 8 fontsize //
	// Need to turn the display back on for use //
	LCD_write_instruction(LCD_4bit_displayON);
	_delay_us(80); // delay must be >37us //
}


void LCD_E_RS_init()
{
	// Set up the E and RS lines to active low for the reset function //
	PORTB &= ~(1<<LCD_EnablePin);
	PORTB &= ~(1<<LCD_RegisterSelectPin);
}


// Send a byte of data to the LCD module //
void LCD_write_4bits(uint8_t data)
{
	// we are only interested in sending the data to the upper 4 bits of PORTD //
	PORTD &= 0x0F; // ensure the upper nybble of PORTD is cleared //
	PORTD |= data;

	// The data is now sitting in the upper nybble of PORTD - need to pulse enable to send it //
	LCD_EnablePulse(); // Pulse the enable to write/read the data //
}


// Pulse the Enable pin on the LCD controller to write/read the data lines - should be at least 230ns pulse width //
void LCD_EnablePulse()
{
	// Set the enable bit low -> high -> low //
	//PORTB &= ~(1<<LCD_EnablePin); // Set enable low //
	//_delay_us(1) // wait to ensure the pin is low //
	PORTB |= (1<<LCD_EnablePin); // set enable high //
	_delay_us(1); // wait to ensure the pin is high // 
	PORTB &= ~(1<<LCD_EnablePin); // set enable low //
	_delay_us(1); // wait to ensure the pin is high //
}


// Write an instruction in 4-bit mode - need to send the upper nybble first and then the lower nybble //
void LCD_write_instruction(uint8_t instruction)
{
	// ensure RS is low //
	//PORTB &= ~(1<<LCD_RegisterSelectPin);
	LCD_E_RS_init(); // set the E and RS pins active low for each LCD reset //

	LCD_write_4bits(instruction); // write the high nybble first //
	LCD_write_4bits(instruction<<4); // write the low nybble //

}


// write a character to the dislpay //
void LCD_write_char(char data)
{
	// set up the E and RS lines for data writing //
	PORTB |= (1<<LCD_RegisterSelectPin); // Ensure RS pin is set high //
	PORTB &= ~(1<<LCD_EnablePin); // Ensure the enable pin is low //
	LCD_write_4bits(data); // write the upper nybble //
	LCD_write_4bits(data<<4); // write the lower nybble //
	_delay_us(80);
}
