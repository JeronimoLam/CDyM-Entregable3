#include "UART.h"

Buffer_TX TX_buffer;
Buffer_RX RX_buffer;

static uint16_t words_counter = 0;

// @brief	Handler de interrupcion para la transmision UART. Interrumpe cuando UDR0 esta vacio
// @param
// @return
ISR(USART_RX_vect){

	// Se lee el dato de UDR0 al buffer de lectura
	if (!RX_buffer_is_full()) {
		set_RX_data_UDR0();

		// Si se encontro el final de una palabra
		if ((RX_buffer.data[RX_buffer.index_escritura]) == '\n')
		{
			// Incrementa la cantidad de palabras en el buffer
			words_counter++;
		}
		inc_RX_index_escritura();
	}
	else {
		// Se deshabilitan las interrupciones por RX en el caso de que el buffer RX est� lleno
		SerialPort_RX_Interrupt_Disable();
	}
}

// @brief	Handler de interrupcion para la recepcion UART. Interrumpe cuando hay un dato en UDR0
// @param
// @return
ISR(USART_UDRE_vect){
	// Si el buffer TX est� lleno se deshabilitan las interrupciones por TX
	if(TX_buffer_is_full() == 1){
		SerialPort_TX_Interrupt_Disable();
	}
	// Se escribe en el buffer y se avanza en el indice de lectura
	else{
		if (TX_buffer.data[TX_buffer.index_lectura] != '\0') {
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
	// Si el buffer TX tiene un unico espacio disponible
	if ((TX_buffer.index_escritura + 1) % BUFFER_TX_LEN == TX_buffer.index_lectura){

		// Se escribe en el mismo el caracter de salto de linea
		TX_buffer.data[TX_buffer.index_escritura] = '\n';
		inc_TX_index_escritura();

		// Se retorna "false", indicando que no se pueden enviar mas bytes.
		return 0;
	}
	// Hay espacio en el buffer
	else{
		// Se carga en la posicion index_escirtura del TX buffer el byte data
		TX_buffer.data[TX_buffer.index_escritura] = data;
		inc_TX_index_escritura();

		// Se habilitan las interrupciones por TX para que data sea enviado
		SerialPort_TX_Interrupt_Enable();
		return 1;
	}
}

// @brief	Escribe una string en buffer de transmision agregando un \r\n al final
// @param	STR_PTR: string a escribir
// @return	void
void UART_Write_String_To_Buffer(char* STR_PTR)
{
	uint8_t i = 0;
	uint8_t is_not_full = 1;
	// Itera transmitiendo los caracteres de STR_PTR mediante la UART. En el caso de que el buffer
	// este lleno, no se transmitiran mas caracteres.
	while ( STR_PTR [ i ] != '\0' && is_not_full){
		is_not_full = UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
	if (is_not_full){
		UART_Write_Char_To_Buffer ('\r');
		UART_Write_Char_To_Buffer ('\n');
	}
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
	return ((TX_buffer.index_lectura) == TX_buffer.index_escritura);
}

char RX_buffer_is_full(){
	return ((RX_buffer.index_lectura == RX_buffer.index_escritura)  && (words_counter > 0));
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
