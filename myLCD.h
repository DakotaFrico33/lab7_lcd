#ifndef myLCD_H
#define myLCD_H


// Helpful LCD control defines //
#define LCD_Reset				0b00110000 // reset the LCD to put in 4-bit mode //
#define LCD_4bit_enable			0b00101000 // 4-bit data - can't set the line dislpay or fonts until this is set //
#define LCD_4bit_mode			0b00010100 // 2-line display, 5 x 8 font //
#define LCD_4bit_displayOFF		0b00001000 // set display off //
#define LCD_4bit_displayON		0b00001100 // set display on - no blink //
#define LCD_4bit_displayCLEAR	0b00000001 // replace all chars with "space" //
#define LCD_4bit_entryMODE		0b00000110 // set cursor to write/read from left -> right //
#define LCD_4bit_cursorSET		0b10000000 // set cursor posiion //
#define LCD_4bit_lineOne		0b00000010

// For two line mode //
#define LineOneStart	0x00
#define	LineTwoStart	0x40 // must set DDRAM address in LCD controller for line two //

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
int keyCheck(unsigned char , unsigned char, char, char *);
int lineChange(int, char *);


#endif