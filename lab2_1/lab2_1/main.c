/*
 * lab2_1.c
 *
 * Created: 1/30/2025 5:16:18 PM
 * Author : njfg0
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "lcd/lcd.h"
#include "adc/adc.h"

//VARIABLES
uint8_t valor_pot1=0;
uint8_t valor_pot2=0;
uint8_t switch_pot=0;
uint8_t change_value_pot1=0;
uint8_t change_value_pot2=0;


int main(void)
{	
	cli();
	initLCD8b();
	initadc();
	ADCSRA|=(1<<ADSC);
	sei();
	LCD_Set_Cursor(1,1);
	LCD_write_String("S1:");
	LCD_Set_Cursor(7,1);
	LCD_write_String("S2:");
	LCD_Set_Cursor(13,1);
	LCD_write_String("S3:");
	
	uint16_t prev_valor_pot1 = 255;
	uint16_t prev_valor_pot2 = 255;
    /* Replace with your application code */
    while (1) 
    {
		if (change_value_pot1==1||change_value_pot2==1){
			change_value_pot1=0;
			change_value_pot2=0;
			
			//comandos_LCD(0b0001);
			if (valor_pot1 != prev_valor_pot1 || valor_pot2 != prev_valor_pot2) {
				 prev_valor_pot1 = valor_pot1;
				 prev_valor_pot2 = valor_pot2;
			
				float mpot1=(valor_pot1*5.0)/255;
				float mpot2=(valor_pot2*5.0)/255;
			
				uint16_t enterov1=(int)mpot1;
				uint16_t decimalv1=(int)((mpot1-enterov1)*100);
			
				uint16_t enterov2=(int)mpot2;
				uint16_t decimalv2=(int)((mpot2-enterov2)*100);
			
				char mensaje1[5];
				LCD_Set_Cursor(0,2);
				mensaje1[0]='0'+enterov1;
				mensaje1[1]='.';
				mensaje1[2]='0'+(decimalv1/1);
				mensaje1[3]='0'+(decimalv1%10);
				mensaje1[4]='V';
				mensaje1[5]='\0';
				LCD_write_String(mensaje1);
			
				char mensaje2[5];
				LCD_Set_Cursor(6,2);
				mensaje2[0]='0'+enterov2;
				mensaje2[1]='.';
				mensaje2[2]='0'+(decimalv2/1);
				mensaje2[3]='0'+(decimalv2%10);
				mensaje2[4]='V';
				mensaje2[5]='\0';
				LCD_write_String(mensaje2);
			}
		}
    }
}
ISR(ADC_vect){
	if (switch_pot==0){
		ADMUX=0;
		ADMUX|=((1<<MUX1)|(1<<MUX2));
		valor_pot1=ADCH;
		switch_pot=1;
		change_value_pot1=1;
		}else{
		ADMUX=0;
		ADMUX|=((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
		valor_pot2=ADCH;
		switch_pot=0;
		change_value_pot2=1;
	}
	ADCSRA|=(1<<ADIF);
}

