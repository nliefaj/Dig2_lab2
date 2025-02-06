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
#include <stdlib.h>

#include "lcd/lcd.h"
#include "adc/adc.h"
#include "com_uart/com_uart.h"

//VARIABLES
uint8_t valor_pot1=0;
uint8_t valor_pot2=0;
uint8_t switch_pot=0;
uint8_t change_value_pot1=0;
uint8_t change_value_pot2=0;
volatile char buffRX;
int contador=0;
uint8_t leer_uart=0;


int main(void)
{	
	cli();
	DDRC=0;
	initUART9600();
	initadc();
	initLCD8b();
	
	//ADCSRA|=(1<<ADSC);
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
	
		//PORTC=(1<<valor_pot1);
		if (change_value_pot1==1||change_value_pot2==1){//||change_value_pot2==1
			change_value_pot1=0;
			change_value_pot2=0;
			
			//comandos_LCD(0b0001);
			if (valor_pot1 != prev_valor_pot1|| valor_pot2 != prev_valor_pot2) {//|| valor_pot2 != prev_valor_pot2
				 prev_valor_pot1 = valor_pot1;
				 prev_valor_pot2 = valor_pot2;
			
				float mpot1=(valor_pot1*5.0)/255.0;
				float mpot2=(valor_pot2*5.0)/255.0;
			
				int enterov1=(int)mpot1;
				int decimalv1=(int)((mpot1-enterov1)*100);
			
				int enterov2=(int)mpot2;
				int decimalv2=(int)((mpot2-enterov2)*100);
			
				char mensaje1[5];
				LCD_Set_Cursor(0,2);
				mensaje1[0]='0'+enterov1;
				mensaje1[1]='.';
				mensaje1[2]='0'+(decimalv1/10);
				mensaje1[3]='0'+(decimalv1%10);
				mensaje1[4]='V';
				mensaje1[5]='\0';
				
				LCD_write_String(mensaje1);
								
				
				char mensaje2[5];
				LCD_Set_Cursor(6,2);
				mensaje2[0]='0'+enterov2;
				mensaje2[1]='.';
				mensaje2[2]='0'+(decimalv2/10);
				mensaje2[3]='0'+(decimalv2%10);
				mensaje2[4]='V';
				mensaje2[5]='\0';
				LCD_write_String(mensaje2);
				
				if(leer_uart==1){
					if(buffRX=='+'){
						contador+=1;
						if (contador==20)
						{
							contador=0;
						}
						leer_uart=0;
					}
					if(buffRX=='-'){
						contador-=1;
						if (contador==-1)
						{
							contador=20;
						}
						leer_uart=0;
					}
				}
				
				//Mostrar el tercer sensor
				char mensaje3[3];
				LCD_Set_Cursor(12,2);
				mensaje3[0]='0'+(contador/10);//decenas
				mensaje3[1]='0'+(contador%10);//unidades
				mensaje3[2]='V';
				mensaje3[3]='\0';
				LCD_write_String(mensaje3);
			}
		}
    }
}

ISR(ADC_vect){
	//ADMUX=0;
	//valor_pot1=ADCH;
	//change_value_pot1=1;
	ADCSRA &= ~(1<<ADEN);
	if (switch_pot==0){
			ADMUX|= (1<<MUX0);
			
			valor_pot1=ADCH;
			switch_pot+=1;
			change_value_pot1=1;
		}else if (switch_pot==1){
			ADMUX&=~(1<<MUX0);
			valor_pot2=ADCH;
			switch_pot=0;
			change_value_pot2=1;
	}
	ADCSRA |= (1<<ADEN);
	ADCSRA|=(1<<ADSC);
	ADCSRA|=(1<<ADIF);
	
}
ISR(USART_RX_vect){
	leer_uart=1;
	buffRX=UDR0;
}

