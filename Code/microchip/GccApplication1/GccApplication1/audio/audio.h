#ifndef AUDIO_H_

    #include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <avr/pgmspace.h>

	#define CANT_SONGS 4

	void sound(unsigned int freq, unsigned int dur);
	void play_song();
	void start_song();
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
    unsigned char get_is_song_playing();
	char *get_song_playing();
	const char* get_song_from_menu(uint8_t index);



    extern const char *rtttl_library[];

#define AUDIO_H_





#endif /* AUDIO_H_ */
