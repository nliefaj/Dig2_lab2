/*
 * adc.c
 *
 * Created: 2/5/2025 11:45:01 PM
 *  Author: njfg0
 */ 
#include "adc.h"
void initadc(void){
ADMUX=0;
ADCSRA=0;

ADMUX|=(1<<REFS0);
ADMUX|=(1<<ADLAR);
ADCSRA=0;
ADCSRA|=(1<<ADEN)|(1<<ADIE);
ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

ADCSRB=0;
}