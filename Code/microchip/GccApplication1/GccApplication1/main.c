/*
 * EjemploTimerRingtone.c
 *
 * Created: 23/10/2020 08:26:59 p. m.
 * Autor:								Pereira F?bio (01/09/2008) - Para un microcontrolador Freescale HCS08
 * Autor migraci?n / modificaci?n:		Perri Victor
 * Asignatura:							Dise?o de Controladores Digitales
-----------------------------------------------------------*/

#include "main.h"
#include "audio/audio.h"
#include "serialPort/serialPort.h"
#include "UART/UART.h"

uint8_t FLAG_datos_recibidos = 0;

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


ISR(USART_RX_vect){
	set_RX_data_UDR0(); // BufferRX[index_escritura] = UDR0
	inc_RX_index_escritura(); // index_escritura++
	if (get_RX_data_index_lectura() == (uint8_t)'\n') {
		set_RX_data('\0');
		FLAG_datos_recibidos=1;
	}
}

ISR(USART_UDRE_vect){
	UDR0 = get_TX_data(get_TX_index_lectura()); // BufferTX[index_lectura]
	inc_TX_index_lectura();						// index_lectura++
	if (!hay_datos_TX_buffer()) {	// buffer_len = 8
		reset_TX_index();
		SerialPort_TX_Interrupt_Disable();
	}
}



// void MENU_Show_Menu(void)
// {
// 	//El men� se escribe en el buffer de transmisi�n
// 	UART_Write_String_To_Buffer("Menu:\n\r");
// 	UART_Write_String_To_Buffer("a � Read PORT1\n\r");
// 	UART_Write_String_To_Buffer("b � Read PORT2\n\r");
// 	UART_Write_String_To_Buffer("? : ");
// }

// void MENU_Command_Update(void)
// {
// 	char ch;
// 	// Check for user inputs
// 	if ( UART_Get_Char_From_Buffer ( &ch ) != 0)
// 	{
// 	MENU_Perform_Task ( Ch );
// 	MENU_Show_Menu ();
// }
// }

const char msjBienvenida [] = "Bienvenido al selector de ringtones! Canciones disponibles: ";
#define LONGBIENVENIDA 59
const char msjPlay[] = "PLAY: Reproduce la cancion seleccionada";
#define LONGPLAY 39
const char msjStop[] = "STOP: Detiene la reproduccion del sonido en curso";
#define LONGSTOP 49
const char msjNum[] = "NUM: Numero de cancion a seleccionar de la lista [1 a N]";
#define LONGNUM 56

const char msjReset[] ="RESET: Reinicia el sistema al estado inicial";
#define LONGRESET 44
uint8_t cancionSeleccionada=0;

int main(void)
{
	// Declaraciones de variables

	unsigned char song_sel;


	// ------------------------ Timer 0 ------------------------

	// Configuro una interrupci?n cada 1 mseg
	// OCR0A = 248;			//124 para 8MHz y 248 para 16MHz
	// TCCR0A = (1<<WGM01);   // Modo CTC, clock interno, prescalador 64
	// TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC, clock interno, prescalador 64
	// TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n


	// // ------------------------ Timer 1 ------------------------

	// TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1, modo CTC y salida por pin
	// TCCR1B|=(1<<WGM12)|(1<<CS10);
	// DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida
	// char UART_flag=0;
	// char MENU_flag=0;


	//Habilito la m?scara de interrupciones

	Buffer_Init();
	SerialPort_Init(103); // 9600 baudios para 16MHz
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();

	sei();

	int i = 0;
	uint8_t * string = "hola\r\n\0";

	UART_Write_String_To_Buffer(msjBienvenida);
	UART_Write_String_To_Buffer(msjPlay);
	UART_Write_String_To_Buffer(msjStop);
	UART_Write_String_To_Buffer(msjNum);
	UART_Write_String_To_Buffer(msjReset);

	uint8_t aa = '\r';
	while(1)
	{
		if (FLAG_datos_recibidos == 1) {
			FLAG_datos_recibidos = 0;
			//UART_Write_String_To_Buffer(get_RX_data());
		}

		//Main
		// Send a string to the UART
		//sprintf(string, "%d\r\n", i);
		//i++;
		_delay_ms(500);

		// if (UART_flag) {
		// 	UART_flag=0;
		// 	UART_Update();
		// }
		// if (MENU_flag) {
		// 	MENU_flag=0;
		// 	MENU_Command_Update();
		// }
		int a = 2;
	//	UART_Update();
		// for (song_sel=0;song_sel<11;song_sel++)
		// {
		// 	play_song(rtttl_library[song_sel]); // Reproduzco la canci?n
		// 	// Espero dos segundos antes de comenzar la siguiente canci?n
		// 	set_duration_timer(2000);
		// 	set_sound_playing(1);
		// 	while (get_sound_playing());
		// }
		i++;
	}

	return 0; // Nunca va a alcanzar esta parte
}
