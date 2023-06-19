/*
 * TIMER1.c
 *
 * Created: 6/19/2023 11:55:35 AM
 *  Author: franc
 */ 

#include "TIMER1.h"

void TIMER1_Init(){
	
	TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1, modo CTC y salida por pin
	TCCR1B|=(1<<WGM12)|(1<<CS10);
	DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida
	char UART_flag=0;
	char MENU_flag=0;
}