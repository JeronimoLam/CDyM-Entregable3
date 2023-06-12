/*
 * audio.h
 *
 * Created: 6/5/2023 2:38:04 PM
 *  Author: franc
 */ 


#ifndef AUDIO_H_

    #include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	
	void sound(unsigned int freq, unsigned int dur);
	void play_song();
	void stop_song();
	void set_song(uint8_t num);
    
    // setters
    void set_duration_timer(int duration);
    void set_sound_playing(unsigned int sound_playing_num);
    void set_duration(unsigned char duration_num);
    void set_octave(unsigned char octave_num);
    void set_tempo(unsigned int tempo_num);

    // getters
    int get_duration_timer();
    unsigned int get_sound_playing();
    unsigned char get_duration();
    unsigned char get_octave();
    unsigned int get_tempo();
	const char * AUDIO_get_songs_menu();


    extern const char *rtttl_library[];

#define AUDIO_H_





#endif /* AUDIO_H_ */