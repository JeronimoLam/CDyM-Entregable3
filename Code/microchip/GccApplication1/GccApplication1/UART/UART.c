/*
 * UART.c
 *
 * Created: 6/7/2023 3:33:18 PM
 *  Author: franc
 */
#include "UART.h"


typedef struct {
	uint8_t data[BUFFER_LEN];
	uint16_t index_escritura;
	uint16_t index_lectura;
} Buffer;

Buffer TX_buffer;
Buffer RX_buffer;

void Buffer_Init (void)
{
	TX_buffer.index_escritura = 0;
	TX_buffer.index_lectura = 0;
	RX_buffer.index_escritura = 0;
	RX_buffer.index_lectura = 0;
}

uint8_t get_TX_data (uint8_t index)
{
	return TX_buffer.data[index];
}

uint8_t get_RX_data_index_lectura()
{
	return RX_buffer.data[RX_buffer.index_lectura];
}

uint8_t* get_RX_data()
{
	return RX_buffer.data;
}


uint8_t set_RX_data (uint8_t dato){
	RX_buffer.data[RX_buffer.index_escritura] = dato;
}

uint8_t set_RX_data_UDR0 (){
	RX_buffer.data[RX_buffer.index_escritura] = UDR0;
}

uint8_t get_TX_index_escritura (void){
	return TX_buffer.index_escritura;
}

uint8_t get_TX_index_lectura (void){
	return TX_buffer.index_lectura;
}

void reset_TX_index(void){
	TX_buffer.index_lectura = 0;
	TX_buffer.index_escritura = 0;
}

void reset_TX_index_lectura (void){
	TX_buffer.index_lectura = 0;
}

void reset_TX_index_escritura (void){
	TX_buffer.index_escritura = 0;
}

void inc_RX_index_escritura (void)
{
	RX_buffer.index_escritura++;
}

void inc_RX_index_lectura (void)
{
	RX_buffer.index_lectura++;
}

void inc_TX_index_escritura (void)
{
	TX_buffer.index_escritura++;
}

void inc_TX_index_lectura (void)
{
	TX_buffer.index_lectura++;
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
	if (TX_buffer.index_escritura < BUFFER_LEN)
	{
		SerialPort_TX_Interrupt_Disable();
		TX_buffer.data[TX_buffer.index_escritura] = data;
		TX_buffer.index_escritura++;
		SerialPort_TX_Interrupt_Enable();
	}
	else
	{
		// Write buffer is full
		return ERROR_UART_FULL_BUFF;
	}
}

// h

void UART_Write_String_To_Buffer(char* STR_PTR)
{
	uint8_t i = 0;
	//SerialPort_TX_Interrupt_Disable();
	while ( STR_PTR [ i ] != '\0')
	{
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
	//SerialPort_TX_Interrupt_Enable();
	UART_Write_Char_To_Buffer ('\r');
	UART_Write_Char_To_Buffer ('\n');
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
		UART_Send_Char ( TX_buffer.data[TX_buffer.index_lectura] ); // entrega al perif�rico para enviar
		TX_buffer.index_lectura++;
	}
	else
	{// No hay datos disponibles para enviar
		TX_buffer.index_lectura = 0;
		TX_buffer.index_escritura = 0;
	}
}

char hay_datos_TX_buffer() {
	return (TX_buffer.index_lectura < TX_buffer.index_escritura);
}

char hay_datos_RX_buffer() {
	return (RX_buffer.index_lectura < RX_buffer.index_escritura);
}