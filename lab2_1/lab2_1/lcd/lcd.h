/*
 * lcd.h
 *
 * Created: 1/30/2025 6:05:50 PM
 *  Author: njfg0
 */ 


#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define E (1<<PORTD3)
#define RS (1<<PORTD2)
//inicializar el lcd en 4 bits
void initLCD8b(void);
//escribir un valor en el puerto de salida
void port_disp(char a);
//comandos
void comandos_LCD(char a);
//funcion para enviar u caracter
void LCD_write_char(char d); 




#endif /* LCD_H_ */