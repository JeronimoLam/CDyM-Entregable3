#ifndef UART_H_

	#define BUFFER_TX_LEN 500UL
	#define BUFFER_RX_LEN 100UL
	#define ERROR_UART_FULL_BUFF 0xFF
	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include "../serialPort/serialPort.h"

	typedef struct {
		uint8_t data[BUFFER_TX_LEN];
		uint16_t index_escritura;
		uint16_t index_lectura;
	} Buffer_TX;

	typedef struct {
		uint8_t data[BUFFER_RX_LEN];
		uint16_t index_escritura;
		uint16_t index_lectura;
	} Buffer_RX;

	uint8_t UART_Write_Char_To_Buffer (uint8_t data);
	void UART_Write_String_To_Buffer(char* STR_PTR);
	void UART_Write_String_To_Buffer_No_NewLine(char* STR_PTR);
	uint8_t UART_Receive_data (uint8_t *dato);
	void UART_Buffer_Init();
	void UART_dec_words_counter(void);
	uint16_t UART_get_words_counter(void);
	char TX_buffer_is_full();
	char RX_buffer_is_full();
	
	void inc_RX_index_escritura (void);
	void inc_RX_index_lectura (void);
	void inc_TX_index_escritura (void);
	void inc_TX_index_lectura (void);
	void reset_TX_index_lectura (void);
	void reset_TX_index_escritura (void);
	void reset_TX_index(void);
	uint8_t get_TX_index_escritura (void);
	uint8_t get_TX_index_lectura (void);
	uint8_t get_TX_data (uint8_t index);
	void set_RX_data_UDR0 ();
	uint8_t* get_RX_data();
	uint8_t get_RX_data_index_lectura();
	uint8_t get_FLAG_datos_recibidos(void);

	

#define UART_H_


#endif /* UART_H_ */
