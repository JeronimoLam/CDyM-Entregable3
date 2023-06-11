/*
 * UART.c
 *
 * Created: 6/7/2023 3:33:18 PM
 *  Author: franc
 */
#include "UART.h"


typedef struct {
	uint8_t data[BUFFER_LEN];
	uint16_t indice_escritura;
	uint16_t indice_lectura;
} Buffer;

Buffer TX_buffer;
Buffer RX_buffer;
	// static unsigned TX_index_escritura;
	// static unsigned TX_index_lectura;
uint8_t RX_index_lectura;

uint8_t get_TX_data (uint8_t index)
{
	return TX_buffer.data[index];
}

uint8_t get_TX_index_escritura (void)
{
	return TX_buffer.indice_escritura;
}

uint8_t get_TX_index_lectura (void)
{
	return TX_buffer.indice_lectura;
}

void reset_TX_index_lectura (void)
{
	TX_buffer.indice_lectura = 0;
}

void inc_RX_index_escritura (void)
{
	RX_buffer.indice_escritura++;
}

void inc_RX_index_lectura (void)
{
	RX_buffer.indice_lectura++;
}

void inc_TX_index_escritura (void)
{
	TX_buffer.indice_escritura++;
}

void inc_TX_index_lectura (void)
{
	TX_buffer.indice_lectura++;
}

void UART_Send_Char ( uint8_t dato) {
	//long Timeout = 0;
	//while ( ( ++Timeout ) && ((UCSR0A & (1<<UDRE0))==0));

	//if (Timeout != 0)
		UDR0 = dato;
	//else {
		// TX_UART did not respond � error
	//}
}

uint8_t UART_Write_Char_To_Buffer (uint8_t data)
{
	if (TX_buffer.indice_escritura < BUFFER_LEN)
	{
		TX_buffer.data[TX_buffer.indice_escritura] = data;
		TX_buffer.indice_escritura++;
		SerialPort_TX_Interrupt_Enable();
	}
	else
	{
		// Write buffer is full
		return ERROR_UART_FULL_BUFF;
	}
}

void UART_Write_String_To_Buffer(uint8_t* STR_PTR)
{
	char i = 0;
	while ( STR_PTR [ i ] != "\0")
	{
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
}

uint8_t UART_Receive_data (uint8_t *dato)
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
	if (hay_datos_TX_buffer())
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

char hay_datos_TX_buffer() {
	return (TX_buffer.indice_lectura < TX_buffer.indice_escritura);
}