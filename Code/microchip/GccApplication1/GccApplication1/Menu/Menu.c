#include "menu.h"

const char msjBienvenida [] PROGMEM = "Bienvenido al selector de ringtones! \n";
const char msjSongs [] PROGMEM = "Canciones:";
const char msjCommands [] PROGMEM = "Comandos:";
const char msjPlay[] PROGMEM = "    ==> PLAY: Reproduce la cancion seleccionada";
const char msjStop[] PROGMEM = "    ==> STOP: Detiene la reproduccion del sonido en curso";
const char msjNum[] PROGMEM = "    ==> NUM: Numero de cancion a seleccionar de la lista [1 a N]";
const char msjReset[] PROGMEM = "    ==> RESET: Reinicia el sistema al estado inicial\n";

char msjBuffer[100]; // Adjust the size to the length of the longest string + 1
char songBuffer[20];

// @brief	Utiliza las funciones de transmision de la UART para mostrar un menu de canciones disponibles
// @param	void
// @return	void
void MENU_display_songs(void){
	
	strcpy_P(msjBuffer, msjSongs);
	UART_Write_String_To_Buffer(msjBuffer);

	for (int i = 0; i < CANT_SONGS; i++){
		UART_Write_String_To_Buffer_No_NewLine("	");
		uint8_t n = i+48;
		UART_Write_Char_To_Buffer(n);
		UART_Write_String_To_Buffer_No_NewLine(": ");
		
		strcpy_P(songBuffer, get_song_from_menu(i));
		UART_Write_String_To_Buffer(songBuffer);
	}
}

// @brief	Utiliza las funciones de transmision de la UART para mostrar un menu de comandos
// @param	void
// @return	void
void MENU_display_commands(){
	strcpy_P(msjBuffer, msjCommands);
	UART_Write_String_To_Buffer(msjBuffer);

	strcpy_P(msjBuffer, msjPlay);
	UART_Write_String_To_Buffer(msjBuffer);

	strcpy_P(msjBuffer, msjStop);
	UART_Write_String_To_Buffer(msjBuffer);

	strcpy_P(msjBuffer, msjNum);
	UART_Write_String_To_Buffer(msjBuffer);

	strcpy_P(msjBuffer, msjReset);
	UART_Write_String_To_Buffer(msjBuffer);
}

// @brief	Utiliza las funciones de transmision de la UART para mostrar un mensaje y un menu de bienvenida en consola
// @param	void
// @return	void
void MENU_display_welcome(){
	strcpy_P(msjBuffer, msjBienvenida);
	UART_Write_String_To_Buffer(msjBuffer);
	
	MENU_display_songs();
	UART_Write_String_To_Buffer_No_NewLine("\n");
	MENU_display_commands();
}

// @brief	A partir del buffer de recepcion crea una string utilizando como corte de una palabra el caracter \r
// @param	buffer: Buffer de recepcion con el arreglo de caracteres; substring: donde se retornará la palabra creada
// @return	void
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

// @brief	Determina cuál ha sido el comando ingresado, o si es válido y qué acciones llevar a cabo.
// @param	inpt: string con la cadena ingresada por el usuario.
// @return	void
void MENU_select_option(char * inpt){
	if (strcmp(inpt, "PLAY") == 0){
		start_song();
		UART_Write_String_To_Buffer_No_NewLine("Reproduciendo: ");
		strcpy_P(songBuffer, get_song_playing());
		UART_Write_String_To_Buffer(songBuffer);
		UART_Write_String_To_Buffer_No_NewLine("\r\n");
		
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
				strcpy_P(songBuffer, get_song_playing());
				UART_Write_String_To_Buffer(songBuffer);
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
		
		MENU_display_welcome();

	}
	else{
		UART_Write_String_To_Buffer("ERROR: Comando no encontrado\r\n");
	}
}

// @brief	Procesa la entrada del usuario por consola
// @param	void
// @return	void
void MENU_process_inpt(){
	uint8_t substring[BUFFER_RX_LEN];

	create_substring(get_RX_data(), substring);
	UART_Write_String_To_Buffer(substring);
	if (strcmp(substring, "")){
		MENU_select_option(substring);
	}
}


