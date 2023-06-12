/*
 * Menu.c
 *
 * Created: 6/12/2023 1:53:19 AM
 *  Author: Jero
 */ 

#include "Menu.h"

void create_substring(Buffer* buffer, uint8_t* substring) {
	uint16_t i = buffer->index_lectura;
	uint16_t j = 0;
	
	while (buffer->data[buffer->index_lectura] != '\r') {
		substring[j++] = buffer->data[buffer->index_lectura];
		inc_RX_index_lectura();
	}
	inc_RX_index_lectura();
	inc_RX_index_lectura();
	substring[j] = '\0'; // append null character at the end
}

MENU_process_inpt(){
	uint8_t substring[BUFFER_LEN];
	
	create_substring(get_RX_data(), substring);
	UART_Write_String_To_Buffer(substring);
	MENU_select_option(substring);
}


void MENU_select_option(char * inpt){
	if (strcmp(inpt, "PLAY") == 0){
		UART_Write_String_To_Buffer("PLAYING song\n");
	}
	else if (strcmp(inpt, "STOP") == 0){
		UART_Write_String_To_Buffer("STOPPING song\n");
	}
	else if (strncmp(inpt, "NUM", 3) == 0){
		uint8_t value;
		if (sscanf(inpt, "NUM %d", &value) == 1) {
			// At this point, 'value' contains the number after "NUM"
			// You can use 'value' here
			UART_Write_String_To_Buffer("NUM of song\n");
			
			char msg[50];
			sprintf(msg, "The number is: %d", value);
			UART_Write_String_To_Buffer(msg);
		}
		else {
			// The format of the string was not "NUM X"
			UART_Write_String_To_Buffer("Command usage: NUM [number of song]");
		}
	}
	else if (strcmp(inpt, "RESET") == 0){
		UART_Write_String_To_Buffer("RESETTING system\n");
		
	}
	else{
		UART_Write_String_To_Buffer("Comando no encontrado\r\n");
	}
}
