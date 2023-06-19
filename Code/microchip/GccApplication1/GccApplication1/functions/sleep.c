/*
 * sleep.c
 *
 * Created: 6/19/2023 12:03:00 PM
 *  Author: franc
 */ 

#include "functions.h"

// @brief	Duerme al CPU en SLEEP_MODE_IDLE (permite interrupciones de la UART y de los TIMER0,1)
// @param	void
// @return	void
void sleep(){
	set_sleep_mode(SLEEP_MODE_IDLE);

	// Habilita sleep mode
	sleep_enable();

	// Duerme al cpu
	sleep_cpu();

	// Deshabilita sleep mode
	sleep_disable();
}