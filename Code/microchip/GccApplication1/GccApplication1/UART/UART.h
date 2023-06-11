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
	void UART_Write_String_To_Buffer(uint8_t* STR_PTR);
	uint8_t UART_Receive_data (uint8_t *dato);
	void UART_Update (void);
	void inc_RX_index_escritura (void);
	void inc_RX_index_lectura (void);
	void inc_TX_index_escritura (void);
	void inc_TX_index_lectura (void);
	void reset_TX_index_lectura (void);
	uint8_t get_TX_index_escritura (void);
	uint8_t get_TX_index_lectura (void);
	uint8_t get_TX_data (uint8_t index);
	char hay_datos_TX_buffer();

#define UART_H_





#endif /* UART_H_ */
