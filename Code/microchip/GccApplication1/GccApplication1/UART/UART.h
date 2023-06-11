/*
 * UART.h
 *
 * Created: 6/7/2023 3:34:14 PM
 *  Author: franc
 */ 

#ifndef UART_H_

	#define BUFFER_LEN 8
	#define ERROR_UART_FULL_BUFF 0xFF
	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>

	void UART_Send_Char (char dato);
	uint8_t UART_Write_Char_To_Buffer (const char data);
	void UART_Write_String_To_Buffer(const char* STR_PTR);
	char UART_Receive_data (char *dato);
	void UART_Update (void);

#define UART_H_





#endif /* UART_H_ */