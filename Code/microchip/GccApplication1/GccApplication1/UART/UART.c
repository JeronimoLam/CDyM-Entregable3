/*
 * UART.c
 *
 * Created: 6/7/2023 3:33:18 PM
 *  Author: franc
 */
#include "UART.h"

Buffer_TX TX_buffer;
Buffer_RX RX_buffer;

static uint16_t words_counter = 0;

// @brief	Handler de interrupcion para la transmision UART. Interrumpe cuando UDR0 esta vacio
// @param  
// @return 
ISR(USART_RX_vect){
	
	// Se lee el dato de UDR0 al buffer de lectura
	set_RX_data_UDR0(); 
	
	// Si se encontro el final de una palabra
	if ((RX_buffer.data[RX_buffer.index_escritura]) == '\n')
	{
		// Incrementa la cantidad de palabras en el buffer
		words_counter++;
	}
	inc_RX_index_escritura();
}

// @brief	Handler de interrupcion para la recepcion UART. Interrumpe cuando hay un dato en UDR0
// @param	
// @return	
ISR(USART_UDRE_vect){
	if(TX_buffer_is_full() == 1){
		SerialPort_TX_Interrupt_Disable();
		//SerialPort_RX_Interrupt_Enable();
	}
	// Se escribe en el buffer y se avanza en el indice de lectura
	else{
		if (TX_buffer.data[TX_buffer.index_lectura] != '/0') {	
			UDR0 = TX_buffer.data[TX_buffer.index_lectura];
		}
		inc_TX_index_lectura();
	}
}

/* -------------------- UART FUNCTIONS -------------------- */

// @brief	Inicializa los indices de lectura y escritura de los buffers de recepcion y tranmsion
// @param	void
// @return	void
void UART_Buffer_Init (void)
{
	TX_buffer.index_escritura = 0;
	TX_buffer.index_lectura = 0;
	RX_buffer.index_escritura = 0;
	RX_buffer.index_lectura = 0;
}

// @brief	Escribe un caracter en buffer de transmision si este no esta lleno
// @param	data: caracter a escribir
// @return	1: buffer lleno, 0: carga exitosa
uint8_t UART_Write_Char_To_Buffer (uint8_t data)
{
	if ((TX_buffer.index_escritura + 1) % BUFFER_TX_LEN == TX_buffer.index_lectura){
		//Buffer lleno
		return 1;
	}
	else{
		TX_buffer.data[TX_buffer.index_escritura] = data;
		TX_buffer.index_escritura = (TX_buffer.index_escritura+1)%BUFFER_TX_LEN;
		SerialPort_TX_Interrupt_Enable();
		return 0;
	}
}

// @brief	Escribe una string en buffer de transmision agregando un \r\n al final
// @param	STR_PTR: string a escribir
// @return	void
void UART_Write_String_To_Buffer(char* STR_PTR)
{
	uint8_t i = 0;
	while ( STR_PTR [ i ] != '\0'){
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
	UART_Write_Char_To_Buffer ('\r');
	UART_Write_Char_To_Buffer ('\n');
}

// @brief	Escribe una string en buffer de transmision
// @param	STR_PTR: string a escribir
// @return	void
void UART_Write_String_To_Buffer_No_NewLine(char* STR_PTR)
{
	uint8_t i = 0;
	while ( STR_PTR [ i ] != '\0')
	{
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
}

// @brief	Lee el registro UDR0 y lo almacena
// @param	*dato: ubicacion donde almacenar UDR0
// @return	0: URD0 vacio; 1: Se cargo exitosamente
uint8_t UART_Receive_data (uint8_t *dato)
{
	if ( UCSR0A & (1<<RXC0) ) {
		*dato=UDR0;
		return 1;
	}
	else
		return 0;
}

// @brief	Retorna 1 o 0 segun si el buffer de transmision esta lleno
// @param	void
// @return	0: TX buffer no lleno; 1: TX buffer lleno
char TX_buffer_is_full() {
	return ((TX_buffer.index_lectura) % BUFFER_TX_LEN == TX_buffer.index_escritura);
}


/* -------------------- GETTERS, SETTERS, INC, DEC -------------------- */

uint16_t UART_get_words_counter(void){
	return words_counter;
}

void UART_dec_words_counter(void){
	words_counter--;
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

void set_RX_data_UDR0 (){
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

void inc_RX_index_escritura (void){
	RX_buffer.index_escritura = (RX_buffer.index_escritura+1)%BUFFER_RX_LEN;
}

void inc_RX_index_lectura (void){
	RX_buffer.index_lectura = (RX_buffer.index_lectura+1)%BUFFER_RX_LEN;
}

void inc_TX_index_escritura (void)
{
	TX_buffer.index_escritura = (TX_buffer.index_escritura+1)%BUFFER_TX_LEN;
}

void inc_TX_index_lectura (void)
{
	TX_buffer.index_lectura = (TX_buffer.index_lectura+1)%BUFFER_TX_LEN;
}