/*
 * UART.h
 *
 * Created: 6/7/2023 3:34:14 PM
 *  Author: franc
 */

#ifndef UART_H_

	#define BUFFER_LEN 400
	#define ERROR_UART_FULL_BUFF 0xFF
	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include "../serialPort/serialPort.h"

	void UART_Send_Char (uint8_t dato);
	uint8_t UART_Write_Char_To_Buffer (uint8_t data);
	void UART_Write_String_To_Buffer(char* STR_PTR);
	uint8_t UART_Receive_data (uint8_t *dato);
	void UART_Update (void);
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
	uint8_t set_RX_data (uint8_t dato);
	uint8_t set_RX_data_UDR0 ();
	uint8_t* get_RX_data();
	uint8_t get_RX_data_index_lectura();
	uint8_t get_FLAG_datos_recibidos(void);
	void set_FLAG_datos_recibidos(uint8_t value);
	char hay_datos_TX_buffer();
	void Buffer_Init();

#define UART_H_





#endif /* UART_H_ */
