#ifndef MENU_H_
#define MENU_H_
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <avr/pgmspace.h>
	#include "../UART/UART.h"
	#include "../audio/audio.h"

	void MENU_process_inpt(void);
	void MENU_display_welcome(void);
	void MENU_display_commands(void);
	
	
#endif /* MENU_H_ */