/*
 * UART.c
 *
 * Created: 6/7/2023 3:33:18 PM
 *  Author: franc
 */
#include "UART.h"



Buffer_TX TX_buffer;
Buffer_RX RX_buffer;

static uint8_t FLAG_datos_recibidos = 0;

ISR(USART_RX_vect){
	/*set_RX_data_UDR0(); // BufferRX[index_escritura] = UDR0
	if ((RX_buffer.data[RX_buffer.index_escritura]) == '\n') {
		//set_RX_data('\0');
		FLAG_datos_recibidos=1;
	}
	inc_RX_index_escritura(); // index_escritura++
*/
	//UART_Write_String_To_Buffer("Entre a la interrupcion");
	set_RX_data_UDR0(); // BufferRX[index_escritura]
	if ((RX_buffer.data[RX_buffer.index_escritura]) == '\n')
	{
		//UART_Write_String_To_Buffer("ENCONTRE UN /N");
		//UART_Write_String_To_Buffer("PRIMER CHEQUEO");
	
		//set_RX_data('\0');
		set_FLAG_datos_recibidos(1);
		/*if (get_FLAG_datos_recibidos() == 1){
			UART_Write_String_To_Buffer("Flag en 1");
			
		}
		else{
			UART_Write_String_To_Buffer("Flag en 0");
			
		}*/
		
		if (get_RX_data_index_lectura() == 'S' || get_RX_data_index_lectura()=='R') {
			UART_Write_String_To_Buffer("La primera letra es una S o una R");
			uint8_t substring[BUFFER_RX_LEN];
			create_substring(get_RX_data(), substring);
			UART_Write_String_To_Buffer(substring);
			
			if (strcmp(substring, "STOP") == 0){
				stop_song();
				UART_Write_String_To_Buffer("Stopped song\n");
				set_FLAG_datos_recibidos(0);
			}
			else if (strcmp(substring, "RESET") == 0){
				UART_Write_String_To_Buffer("RESETTING system\n");
				stop_song();
				set_song(0);
		
				MENU_display_options();
				set_FLAG_datos_recibidos(0);
			}
		
		}
		//UART_Write_String_To_Buffer("SEGUNDO CHEQUEO");
		
		/*if (get_FLAG_datos_recibidos() == 1){
			UART_Write_String_To_Buffer("Flag en 1");
			
		}
		else{
			UART_Write_String_To_Buffer("Flag en 0");
			
		}*/
	}
	
	inc_RX_index_escritura();
}

ISR(USART_UDRE_vect){
	/*UDR0 = get_TX_data(get_TX_index_lectura()); // BufferTX[index_lectura]
	if (!hay_datos_TX_buffer()) {	// buffer_len = 8
		//reset_TX_index();
		SerialPort_TX_Interrupt_Disable();
	}
	inc_TX_index_lectura();						// index_lectura++
	*/
	if((TX_buffer.index_lectura) % BUFFER_TX_LEN == TX_buffer.index_escritura){
		SerialPort_TX_Interrupt_Disable();
		SerialPort_RX_Interrupt_Enable();
	}
	else{
		if (TX_buffer.data[TX_buffer.index_lectura] != '/0') {	// buffer_len = 8
			UDR0 = TX_buffer.data[TX_buffer.index_lectura];
		}
		TX_buffer.index_lectura = (TX_buffer.index_lectura+1)%BUFFER_TX_LEN;

	}
}


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

uint8_t get_FLAG_datos_recibidos(void){
	return FLAG_datos_recibidos;
}

void set_FLAG_datos_recibidos(uint8_t value){
	FLAG_datos_recibidos = value;
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
	/*if (TX_buffer.index_escritura != BUFFER_TX_LEN)
	{
		TX_buffer.data[TX_buffer.index_escritura] = data;
		TX_buffer.index_escritura++;
		SerialPort_TX_Interrupt_Enable();
	}
	else
	{
		// Write buffer is full
		return ERROR_UART_FULL_BUFF;
	}*/
	
	if ((TX_buffer.index_escritura + 1) % BUFFER_TX_LEN == TX_buffer.index_lectura){
		//Buffer lleno
	}
	else{
		TX_buffer.data[TX_buffer.index_escritura] = data;
		TX_buffer.index_escritura = (TX_buffer.index_escritura+1)%BUFFER_TX_LEN;		
		SerialPort_TX_Interrupt_Enable();
	
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
	UART_Write_Char_To_Buffer ('\r');
	UART_Write_Char_To_Buffer ('\n');
	SerialPort_TX_Interrupt_Enable();
	
}

void UART_Write_String_To_Buffer_No_NewLine(char* STR_PTR)
{
	uint8_t i = 0;
	//SerialPort_TX_Interrupt_Disable();
	while ( STR_PTR [ i ] != '\0')
	{
		UART_Write_Char_To_Buffer ( STR_PTR [ i ] );
		i++;
	}
	SerialPort_TX_Interrupt_Enable();
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
	return (TX_buffer.index_lectura != TX_buffer.index_escritura);
}

char hay_datos_RX_buffer() {
	return (RX_buffer.index_lectura < RX_buffer.index_escritura);
}

