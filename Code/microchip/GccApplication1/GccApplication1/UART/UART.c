/*
 * UART.c
 *
 * Created: 6/7/2023 3:33:18 PM
 *  Author: franc
 */ 
#include "UART.h"


typedef struct {
	uint8_t data[BUFFER_LEN];
	uint8_t indice_escritura;
	uint8_t indice_lectura;	
} Buffer;

Buffer TX_buffer;
Buffer RX_buffer;
	// static unsigned TX_index_escritura;
	// static unsigned TX_index_lectura;
uint8_t RX_index_lectura;

void UART_Send_Char (char dato) {
	long Timeout = 0;
	while ( ( ++Timeout ) && ((UCSR0A & (1<<UDRE0))==0));
	
	if (Timeout != 0)
		UDR0 = dato;
	else {
		// TX_UART did not respond � error
	}
}

uint8_t UART_Write_Char_To_Buffer (const char data)
{
	if (TX_buffer.indice_escritura < BUFFER_LEN)
	{
		TX_buffer.data[TX_buffer.indice_escritura] = data;
		TX_buffer.indice_escritura++;
	}
	else
	{
		// Write buffer is full
		return ERROR_UART_FULL_BUFF;
	}
}

void UART_Write_String_To_Buffer(const char* STR_PTR)
{
	char i = 0;
	while ( STR_PTR [ i ] != "\0")
	{
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
}

char UART_Receive_data (char *dato)
{
	if ( UCSR0A & (1<<RXC0) ) {
		*dato=UDR0;
		return 1;
	}
	else
		return 0;
}

void UART_Update (void)
{
	// Hay byte en el buffer Tx para transmitir?
	if (TX_buffer.indice_lectura < TX_buffer.indice_escritura)
	{
		UART_Send_Char ( TX_buffer.data[TX_buffer.indice_lectura] ); // entrega al perif�rico para enviar
		TX_buffer.indice_lectura++;
	}
	else
	{// No hay datos disponibles para enviar
		TX_buffer.indice_lectura = 0;
		TX_buffer.indice_escritura = 0;
	}
}