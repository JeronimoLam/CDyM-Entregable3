/*
 * Menu.c
 *
 * Created: 6/12/2023 1:53:19 AM
 *  Author: Jero
 */

#include "menu.h"

const char msjBienvenida [] = "Bienvenido al selector de ringtones! \n";
const char msjSongs [] = "Canciones:";
const char msjCommands [] = "Comandos:";
const char msjPlay[] = "    ==> PLAY: Reproduce la cancion seleccionada";
const char msjStop[] = "    ==> STOP: Detiene la reproduccion del sonido en curso";
const char msjNum[] = "    ==> NUM: Numero de cancion a seleccionar de la lista [1 a N]";
const char msjReset[] = "    ==> RESET: Reinicia el sistema al estado inicial\n";

void MENU_display_songs(void){
	UART_Write_String_To_Buffer(msjSongs);

	const char ** songs = AUDIO_get_songs_menu();
	for (int i = 0; i < CANT_SONGS; i++){
		UART_Write_String_To_Buffer_No_NewLine("	");
		uint8_t n = i+48;
		UART_Write_Char_To_Buffer(n);
		UART_Write_String_To_Buffer_No_NewLine(": ");
		UART_Write_String_To_Buffer(songs[i]);
	}
}

void MENU_display_commands(){
	UART_Write_String_To_Buffer(msjCommands);
	UART_Write_String_To_Buffer(msjPlay);
	UART_Write_String_To_Buffer(msjStop);
	UART_Write_String_To_Buffer(msjNum);
	UART_Write_String_To_Buffer(msjReset);
}

void MENU_display_welcome(){
	UART_Write_String_To_Buffer(msjBienvenida);
	MENU_display_songs();
	UART_Write_String_To_Buffer_No_NewLine("\n");
	MENU_display_commands();

}

void create_substring(Buffer_RX* buffer, uint8_t* substring) {
	uint16_t j = 0;

	while (buffer->data[buffer->index_lectura] != '\r' && j < 7) {
		substring[j++] = buffer->data[buffer->index_lectura];
		inc_RX_index_lectura();
	}
	inc_RX_index_lectura();
	inc_RX_index_lectura();
	substring[j] = '\0'; // append null character at the end
}


void MENU_select_option(char * inpt){
	if (strcmp(inpt, "PLAY") == 0){
		start_song();
		UART_Write_String_To_Buffer_No_NewLine("Reproduciendo: ");
		UART_Write_String_To_Buffer_No_NewLine(get_song_playing());
		UART_Write_String_To_Buffer("\r\n");
		
	}
	else if (strncmp(inpt, "NUM", 3) == 0){

		if (get_is_song_playing()) {
			UART_Write_String_To_Buffer("ERROR: Hay una cancion en reproduccion\r\n");
			return;
		}

		// Si el formato es "NUM X"
		if (inpt[3] == ' ' && inpt[5] == '\0') {

			// value contiene el valor "X"
			uint8_t value = inpt[4] - '0';

			if (value >= 0 && value < CANT_SONGS){
				set_song(value);
				UART_Write_String_To_Buffer_No_NewLine("Se selecciono: ");
				UART_Write_String_To_Buffer(get_song_playing());
				UART_Write_String_To_Buffer_No_NewLine("\n");
			}
			else{
				UART_Write_String_To_Buffer("Ingrese un numero adecuado");
				MENU_display_songs();
				UART_Write_String_To_Buffer("\n");
			}
		}
		else {
			// Si el formato no es "NUM X"
			UART_Write_String_To_Buffer("Uso del comando: NUM [numero de cancion]\n");
		}
	}
	else if (strcmp(inpt, "STOP") == 0){

		if (get_is_song_playing()){
			UART_Write_String_To_Buffer("Reproduccion detenida\n");
		}
		else {
			UART_Write_String_To_Buffer("No hay cancion en reproduccion\n");
		}
		
		stop_song();

	}
	else if (strcmp(inpt, "RESET") == 0){
		UART_Write_String_To_Buffer("Reestableciendo el sistema\n");
		stop_song();
		set_song(0);
		// Se resetean los buffers
		/*
		cli();
		Buffer_Init();
		sei();
		UART_Write_String_To_Buffer("RESETTING system\n");
		*/
		// Reimprime el menu
		
		MENU_display_welcome();

	}
	else{
		UART_Write_String_To_Buffer("ERROR: Comando no encontrado\r\n");
	}
}

void MENU_process_inpt(){
	uint8_t substring[BUFFER_RX_LEN];

	create_substring(get_RX_data(), substring);
	UART_Write_String_To_Buffer(substring);
	if (strcmp(substring, "")){
		MENU_select_option(substring);
	}
}


