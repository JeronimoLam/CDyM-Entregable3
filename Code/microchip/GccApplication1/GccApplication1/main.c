#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "Menu/Menu.h"
#include "UART/UART.h"

// Control de la duraci?n del sonido
ISR (TIMER0_COMPA_vect) // ISR para la interrupci?n de comparaci?n del Timer 0
{
	unsigned int duration_timer = get_duration_timer();
	if (duration_timer) {
		duration_timer--; // Decremento el timer si > 0
		set_duration_timer(duration_timer);
	}
	else                                  // si timer es = 0
	{
		TCCR1A=0;	// Desactivo el timer 1
		set_sound_playing(0);                  // Borro el flag para avisar que no hay una nota sonando
	}
}


int main(void)
{
	// Declaraciones de variables

	unsigned char song_sel;


	// ------------------------ Timer 0 ------------------------

	// Configuro una interrupci?n cada 1 mseg
	OCR0A = 248;			//124 para 8MHz y 248 para 16MHz
	TCCR0A = (1<<WGM01);   // Modo CTC, clock interno, prescalador 64
	TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC, clock interno, prescalador 64
	TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n


	// // ------------------------ Timer 1 ------------------------

	TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1, modo CTC y salida por pin
	TCCR1B|=(1<<WGM12)|(1<<CS10);
	DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida
	char UART_flag=0;
	char MENU_flag=0;


	//Habilito la mAscara de interrupciones
	Buffer_Init();
	SerialPort_Init(103); // 9600 baudios para 16MHz
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();

	MENU_display_welcome();
	sei();
	
	while(1)
	{
		if (get_FLAG_datos_recibidos() == 1) {
			set_FLAG_datos_recibidos(0);
			
			// procesamiento BUffer_Rx
			MENU_process_inpt();
		}
	}
	return 0;
}



