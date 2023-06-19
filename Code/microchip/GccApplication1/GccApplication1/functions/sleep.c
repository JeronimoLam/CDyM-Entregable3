/*
 * sleep.c
 *
 * Created: 6/19/2023 12:03:00 PM
 *  Author: franc
 */ 

#include "functions.h"

void sleep(){
	set_sleep_mode(SLEEP_MODE_IDLE);

	// Habilita sleep mode
	sleep_enable();

	// Duerme al cpu
	sleep_cpu();

	// Deshabilita sleep mode
	sleep_disable();
}