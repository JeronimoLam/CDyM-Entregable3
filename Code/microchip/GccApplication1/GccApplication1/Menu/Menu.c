/*
 * Menu.c
 *
 * Created: 6/12/2023 1:53:19 AM
 *  Author: Jero
 */ 

#include "Menu.h"

const char msjBienvenida [] = "Bienvenido al selector de ringtones! Canciones disponibles: \n";
#define LONG_BIENVENIDA 59
const char msjPlay[] = "PLAY: Reproduce la cancion seleccionada";
#define LONG_PLAY 39
const char msjStop[] = "STOP: Detiene la reproduccion del sonido en curso";
#define LONG_STOP 49
const char msjNum[] = "NUM: Numero de cancion a seleccionar de la lista [1 a N]";
#define LONG_NUM 56
const char msjReset[] ="RESET: Reinicia el sistema al estado inicial\n";
#define LONG_RESET 44

void MENU_display_options(void){
	UART_Write_String_To_Buffer(msjPlay);
	UART_Write_String_To_Buffer(msjStop);
	UART_Write_String_To_Buffer(msjNum);
	UART_Write_String_To_Buffer(msjReset);
}

void MENU_display_options_bienvenida(){
	UART_Write_String_To_Buffer(msjBienvenida);
}

void create_substring(Buffer_RX* buffer, uint8_t* substring) {
	uint16_t j = 0;
	
	while (buffer->data[buffer->index_lectura] != '\r') {
		substring[j++] = buffer->data[buffer->index_lectura];
		inc_RX_index_lectura();
	}
	inc_RX_index_lectura();
	inc_RX_index_lectura();
	substring[j] = '\0'; // append null character at the end
}

void MENU_process_inpt(){
	uint8_t substring[BUFFER_RX_LEN];
	
	create_substring(get_RX_data(), substring);
	UART_Write_String_To_Buffer(substring);
	MENU_select_option(substring);
}


void MENU_select_option(char * inpt){
	if (strcmp(inpt, "PLAY") == 0){
		
		UART_Write_String_To_Buffer("Playing song\n");
		play_song();
		
	}
	else if (strcmp(inpt, "STOP") == 0){
		
		stop_song();
		UART_Write_String_To_Buffer("Stopped song\n");
		
	}
	else if (strncmp(inpt, "NUM", 3) == 0){
			UART_Write_String_To_Buffer("ok\n");
			
		uint8_t value;
		// Si el formato es "NUM X"
		if (sscanf(inpt, "NUM %d", &value) == 1) {
			UART_Write_String_To_Buffer("ok 1\n");
			
			
			// value contiene el valor "X"
			
			char msg[50];
			UART_Write_String_To_Buffer("ok 2\n");
			
			sprintf(msg, "Song selected: %d\n", value);
			UART_Write_String_To_Buffer(msg);
			set_song(value);
			
			
		}
		else {
			
			// Si el formato no es "NUM X"
			UART_Write_String_To_Buffer("Command usage: NUM [number of song]");
			
		}
	}
	else if (strcmp(inpt, "RESET") == 0){
		UART_Write_String_To_Buffer("RESETTING system\n");
		stop_song();
		set_song(1);
		// Se resetean los buffers
		/*
		cli();
		Buffer_Init();
		sei();
		UART_Write_String_To_Buffer("RESETTING system\n");
		*/
		// Reimprime el menu
		MENU_display_options();
		
	}
	else{
		UART_Write_String_To_Buffer("Comando no encontrado\r\n");
	}
}
