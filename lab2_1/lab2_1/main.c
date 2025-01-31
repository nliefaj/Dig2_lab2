/*
 * lab2_1.c
 *
 * Created: 1/30/2025 5:16:18 PM
 * Author : njfg0
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>

#include "lcd/lcd.h"


int main(void)
{	
	initLCD8b();
	LCD_write_char('H');
	LCD_write_char('O');
	LCD_write_char('L');
	LCD_write_char('A');
	LCD_write_char('2');
	LCD_write_char('3');
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

