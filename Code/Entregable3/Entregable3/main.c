
 
 //1-transmitir G. Ver silulador as7, tregistros uart y tiempo que tarda en transmitir un caracter.
/*
#include <avr/io.h>
#define F_CPU 16000000UL		// 16 MHz
#include <util/delay.h>

 int main(void)
 {
	 //initialize the USART
	 UCSR0B = (1<<TXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = 'G';						 //transmit ‘G’ letter
		 _delay_ms(500);
	 }
	 return 0;
 }
 */
 
 /*
 //2-LOOPBACK con polling 
 #include <avr/io.h>
 #define F_CPU 16000000UL		// 16 MHz
 #include <util/delay.h>
 
 int main(void)
 {
	 volatile unsigned char dato;
	 //initialize the USART
	 UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = 'G';						 //transmit ‘G’ letter
		 while (! (UCSR0A & (1<<RXC0))); //wait until new data
		 dato = UDR0;
	 }
	 return 0;
 }
 //3-eco de caracter con polling (no se puede simular en as7 la recepcion)

 #include <avr/io.h>
 #define F_CPU 16000000UL		// 16 MHz
 #include <util/delay.h>

 int main(void)
 {
	 volatile unsigned char dato;
	 DDRB=0xFF;
	 //initialize the USART
	 UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<RXC0))); //wait until new data
		 dato = UDR0;
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = dato;						 //transmit dato
		 PORTB= dato;
	 }
	 return 0;
 }

 //4- transmitir cadenas +  eco

// Archivo de cabecera del Microcontrolador
#include <avr/io.h>
#include "serialPort.h"

 #define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

 //mensajes de bienvenida y despedida
 char msg1[] = "Hola Mundo, si presiona 's' termina el programa, por favor ingrese una tecla:\n\r";
 char msg2[] = "\n\rHasta luego!";

 int main(void)
 {
	 volatile char dato = 0;
	 
	 SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida

	 while(1)
	 {
		 SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
		 dato = SerialPort_Recive_Data();

		 // Si presionan 's' se termina el programa
		 if( dato == 's')
		 {
			 SerialPort_Send_String(msg2);  // Envío el string de despedida
			 while(1);
		 }
		 else
		 {	// Eco:
			 SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
			 SerialPort_Send_Data(dato);			  // Envío el dato recibido
		 }
	 }
	 return 0;
 }
*/
 /*
 //4- transmitir cadenas +  eco usando interrupción Rx
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "serialPort.h"

 #define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

 //mensajes de bienvenida y despedida
 char msg1[] = "Uso de interrup RXC, si presiona 's' termina el programa, por favor ingrese una tecla:\n\r";
 char msg2[] = "\n\rHasta luego!";

 //comunicación con la ISR
 volatile char RX_Buffer=0;

 int main(void)
 {
	 
	 SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida
	 SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
	 sei();								// Activo la mascara global de interrupciones (Bit I del SREG en 1)

	 while(1)
	 {
		 if(RX_Buffer){ // recepción NO Bloqueante
			 // Si presionan 's' se termina el programa
			 if(RX_Buffer == 's'){
				 SerialPort_Send_String(msg2);  // Envío el string de despedida
				 while(1);
			 }
			 else{	// Eco:
				 SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
				 SerialPort_Send_Data(RX_Buffer);			  // Envío el dato recibido
			 }
			 RX_Buffer=0;
		 }
		 //otra tarea
	 }
	 return 0;
 }

 // Rutina de Servicio de Interrupción de Byte Recibido
 ISR(USART_RX_vect){
	 RX_Buffer = UDR0; //la lectura del UDR borra flag RXC
 }

 */
 
 
 /*
 * EjemploTimerRingtone.c
 *
 * Created: 23/10/2020 08:26:59 p. m.
 * Autor:								Pereira F?bio (01/09/2008) - Para un microcontrolador Freescale HCS08
 * Autor migraci?n / modificaci?n:		Perri Victor
 * Asignatura:							Dise?o de Controladores Digitales
-----------------------------------------------------------*/
#include "Audio.h"

volatile unsigned int sound_playing;
unsigned int duration_timer;

int main(void)
{
	// Declaraciones de variables
	sound_playing = 0;
	unsigned char song_sel = 0;
	
	
	
	// ------------------------ Timer 0 ------------------------
	
	// Configuro una interrupci?n cada 1 mseg
	OCR0A = 248;			//124 para 8MHz y 248 para 16MHz 
	TCCR0A = (1<<WGM01);   // Modo CTC, clock interno, prescalador 64
	TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC, clock interno, prescalador 64
	TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n
	
	
	// ------------------------ Timer 1 ------------------------
	
	TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1, modo CTC y salida por pin
	TCCR1B|=(1<<WGM12)|(1<<CS10);
	DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida


	//Habilito la m?scara de interrupciones
	
	sei();
	
	while(1)
	{
		//Main
		for (song_sel=8;song_sel<11;song_sel++)
		{
			song_sel=8;
			play_song(rtttl_library[song_sel]); // Reproduzco la canci?n
			// Espero dos segundos antes de comenzar la siguiente canci?n
			duration_timer = 2000;
			sound_playing = 1;
			while (sound_playing);
		}
	}

	return 0; // Nunca va a alcanzar esta parte
}