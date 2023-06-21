#include "TIMER0.h"

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

void TIMER0_Init(){
	// Configuro una interrupci?n cada 1 mseg
	OCR0A = 248;			//124 para 8MHz y 248 para 16MHz
	TCCR0A = (1<<WGM01);   // Modo CTC, clock interno, prescalador 64
	TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC, clock interno, prescalador 64
	TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n
}