/*
 * Menu.h
 *
 * Created: 6/12/2023 1:53:38 AM
 *  Author: Jero
 */ 


#ifndef MENU_H_
#define MENU_H_
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "../UART/UART.h"
	//#include "../audio/audio.h"

	void MENU_process_inpt(void);
	void MENU_display_options_bienvenida(void);
	void MENU_display_options(void);
	
	
#endif /* MENU_H_ */