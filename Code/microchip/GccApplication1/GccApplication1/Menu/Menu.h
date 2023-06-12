/*
 * Menu.h
 *
 * Created: 6/12/2023 1:53:38 AM
 *  Author: Jero
 */ 


#ifndef MENU_H_
#define MENU_H_
	#include <stdio.h>
	#include <string.h>
	#include "../UART/UART.h"
	#include "../audio/audio.h"

	void MENU_process_inpt();
	void MENU_display_options_bienvenida();
	void MENU_display_options();
	
	
#endif /* MENU_H_ */