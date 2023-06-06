/*
 * main.h
 *
 * Created: 5/29/2023 3:55:03 PM
 *  Author: franc
 */ 


#ifndef MAIN_H_

	#define F_CPU 16000000UL
	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	
	void sound(unsigned int freq, unsigned int dur);
	void play_song(char *song);
	

#define MAIN_H_





#endif /* MAIN_H_ */