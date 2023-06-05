/*
 * main.h
 *
 * Created: 29/05/2023 03:54:31 p. m.
 *  Author: Sharks
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	#include <util/delay.h>
	
	extern volatile unsigned int sound_playing;
	extern unsigned int duration_timer;
	const char *rtttl_library[];
	
	void sound(unsigned int freq, unsigned int dur);
	void play_song(char *song);
	



#endif /* MAIN_H_ */