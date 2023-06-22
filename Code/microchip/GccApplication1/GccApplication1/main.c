#define F_CPU 16000000UL

#include "menu/menu.h"
#include "UART/UART.h"
#include "timer/TIMER0.h"
#include "timer/TIMER1.h"
#include "funciones/functions.h"

int main(void)
{
	// Configuracion de los TIMERs 0,1 para la reproduccion de audio
	TIMER0_Init();
	TIMER1_Init();

	// Inicializacion de los buffers de recepcion y transmision de la UART
	UART_Buffer_Init();

	// Inicializacion y configuracion del periferco UART para transmision serie
	SerialPort_Init(103);					// 9600 baudios para 16MHz
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();

	// Menu de inicio del sistema
	MENU_display_welcome();

	// Activacion global de interrupciones
	sei();

	// Bucle principal (TAREAS DE BACKGROUND)
	while(1){

		// Tarea para la lectura de palabras del buffer de recepcion
		
		if (UART_get_words_counter() > 0) {

			SerialPort_RX_Interrupt_Disable();
			UART_dec_words_counter();			// Seccion critica
			SerialPort_RX_Interrupt_Enable();

			MENU_process_inpt();
		}
		// Tarea para la reproduccion de una nota de la cancions
		else if (get_is_song_playing() == 1){
			play_song();
		}
		else {
			// Se duerme el CPU hasta la proxima interrupcion (IDLE_MODE)
			sleep();
		}
	}
	return 0;
}



