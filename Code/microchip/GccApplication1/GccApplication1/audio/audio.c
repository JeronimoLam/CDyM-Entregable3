#include "audio.h"

const char *rtttl_library[]=
{
	"TheSimpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6",
	"MissionImp:d=4,o=6,b=150:16d5,16d#5,16d5,16d#5,16d5,16d#5,16d5,16d5,16d#5,16e5,16f5,16f#5,16g5,8g5,4p,8g5,4p,8a#5,8p,8c6,8p,8g5,4p,8g5,4p,8f5,8p,8p,8g5,4p,4p,8a#5,8p,8c6,8p,8g5,4p,4p,8f5,8p,8f#5,8p,8a#5,8g5,1d5",
	//"Batman:d=8,o=5,b=160:16a,16g#,16g,16f#,16f,16f#,16g,16g#,4a.,p,d,d,c#,c#,c,c,c#,c#,d,d,c#,c#,c,c,c#,c#,d,d,c#,c#,c,c,c#,c#,g6,p,4g6",
	//"Pinkpanther:d=16,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,p,8f#,8g,p,8c6,8b,p,8d#,8e,p,8b,2a#,2p,a,g,e,d,2e"

	// "Adamsfamily:d=4,o=5,b=160:8c,f,8a,f,8c,b4,2g,8f,e,8g,e,8e4,a4,2f,8c,f,8a,f,8c,b4,2g,8f,e,8c,d,8e,1f,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f",
	// "Argentina:d=4,o=5,b=70:8e.4,8e4,8e4,8e.4,8f4,8g4,8a4,g4,8p,8g4,8a4,8a4,8g4,c,g4,8f4,e.4,8p,8e4,8f4,8g4,8d4,d4,8d4,8e4,8f4,c4,16p,8c4,8d4,8c4,8e4,g4,16p,8g4,8g4,8a4,c,16p",
	 "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6",
	// "killing me softly:d=4,o=5,b=90:p,8e,f,g,8a,a,8g,d,g.,p,8p,8a,g,8f,8e,8e,8f,2c,p,8e,f,g,8a,a,8g,a,b,8b,8c6,8b,16a,8g,16a,2a,2a.",
	 "Wannabe:d=4,o=5,b=125:16g,16g,16g,16g,8g,8a,8g,8e,8p,16c,16d,16c,8d,8d,8c,e,p,8g,8g,8g,8a,8g,8e,8p,c6,8c6,8b,8g,8a,16b,16a,g"
	// "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.",
	// "Zorba2:d=4,o=5,b=125:16c#6,2d6,2p,16c#6,2d6,2p,32e6,32d6,32c#6,2d6,2p,16c#6,2d6,2p,16b,2c6,2p,32d6,32c6,32b,2c6,2p,16a#,2b,p,8p,32c6,32b,32a,32g,32b,2a,2p,32a,32g,32f#,32a,1g,1p,8c#6,8d6,8d6,8d6,8d6,8d6,8d6,8d6,8c#6,8d6,8d6,8d6,8d6,8d6,16e6,16d6,16c#6,16e6,8c#6,8d6,8d6,8d6,8d6,8d6,8d6,8d6,8c#6,8d6,8d6,8d6,8d6,8d6"
};

const char song1[] PROGMEM = "Los Simpsons";
const char song2[] PROGMEM = "Mision Imposible";
const char song3[] PROGMEM = "Indiana Jones";
const char song4[] PROGMEM = "Wannabe";

const char* const songs_menu[] PROGMEM = {song1, song2, song3, song4};

// @brief	Obtiene una cancion del menu de canciones.
// @param	index: indice de la cancion elegida en el arreglo.
// @return	char*: string con el nombre de la canci�n
const char* get_song_from_menu(uint8_t index) {
	return (PGM_P)pgm_read_word(&(songs_menu[index]));
}


// La siguiente matriz almacena las frecuencias de las notas musicales
const unsigned int note[4][12] =
{   // C    C#    D     D#    E     F     F#    G     G#    A     A#    B
	{262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494}, // 4ta octava
	{523,  554,  587,  622,  659,  698,  740,  784,  830,  880,  932,  988}, // 5ta octava
	{1047, 1109, 1175, 1244, 1319, 1397, 1480, 1568, 1660, 1760, 1865, 1976}, // 6ta octava
	{2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3320, 3520, 3728, 3951}  // 7ma octava
};

unsigned int duration_timer;
volatile unsigned int sound_playing=0;
volatile unsigned char is_song_playing=0;
unsigned char duration, octave;
unsigned int tempo;
volatile char *song;
static uint8_t current_song = 0;

volatile unsigned char temp_duration, temp_octave, current_note, dot_flag;
volatile unsigned int calc_duration;

// @brief	Reproduce sonido por el PIN5 del PORTD
// @param	freq: frecuencia en Hz del sonido; dur: duracion en ms del sonido
// @return	void
void sound(unsigned int freq, unsigned int dur)
{
	while (sound_playing);      // Si hay alg?n sonido presente, espero a que termine

	duration_timer = dur;       // Seteo el tiempo de duraci?n

	// Activo la salida y configuro el timer para que genere la se?al de la frecuencia apropiada
	TCCR1A|=(1<<COM1A0);

	// Actualizo el valor de OCR1A para que produzca la nota adecuada
	OCR1A=(8000000/(freq))-1;

	sound_playing = 1;          // Activo el flag para avisar que hay una nota sonando
}

// @brief	Para el sonido y la cancion en reproduccion
// @param	void
// @return	void
void stop_song()
{
	is_song_playing = 0;           // Activo el flag para avisar que hay una nota sonando
	sound_playing = 0;          // Activo el flag para avisar que hay una nota sonando
	TCCR1A&=~(1<<COM1A0);       // Desactivo la salida
}

// @brief	Inicializa las variables necesarias para la reproduccion de la cancion seleccionada en current_song
// @param	void
// @return	void
void start_song() {
	is_song_playing = 1;
	song = rtttl_library[current_song];

	while (*song != ':') song++;  // Busca el primer ':'
	song++;                       // Saltea el primer ':'
	while (*song!=':')            // Repite hasta encontrar ':'
	{
		if (*song == 'd')           // Entra si es el seteo de la duraci?n
		{
			duration = 0;             // Seteo la duraci?n en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Si el caracter es un n?mero, seteo la duraci?n
			if (*song>='0' && *song<='9') duration = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			// Me fijo si el caracter es un n?mero, ya que la diraci?n puede ser de dos d?gitos de largo
			if (*song>='0' && *song<='9')
			{ // Multiplico duraci?n por 10 y le agrego el valor del caracter
				duration = duration*10 + (*song - '0');
				song++;                 // Avanzo al pr?ximo caracter
			}
			while (*song == ',') song++;  // Salteo ','
		}

		if (*song == 'o')           // Entra si es el seteo de la octava
		{
			octave = 0;               // Seteo la octava en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Si el caracter es un n?mero, seteo la octava
			if (*song>='0' && *song<='9') octave = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == ',') song++;  // Salteo ','
		}
		if (*song == 'b')           // Entra si es el seteo del tempo (beats por minuto)
		{
			tempo = 0;                // Seteo el tempo en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Ahora leo el seteo del tempo (puede tener 3 d?gitos de largo)
			if (*song>='0' && *song<='9') tempo = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			if (*song>='0' && *song<='9')
			{
				tempo = tempo*10 + (*song - '0'); // El tempo tiene dos d?gitos
				song++;                 // Avanzo al pr?ximo caracter
				if (*song>='0' && *song<='9')
				{
					tempo = tempo*10 + (*song - '0'); // El tempo tiene tres d?gitos
					song++;               // Avanzo al pr?ximo caracter
				}
			}
			while (*song == ',') song++;  // Salteo ','
		}
		while (*song == ',') song++;    // Salteo ','
	}
	song++;                       // Avanzo al pr?ximo caracter
}

// @brief	Reproduce una cancion con formato RTTTL almacenada en la string song
// @param	void
// @return	void
void play_song()
{
	//UART_Write_Char_To_Buffer('a');
//	                      // Avanzo al pr?ximo caracter
	// read the musical notes
	if (*song && is_song_playing)                 // Repito hasta que el caracter sea null
	{
		current_note = 255;         // Nota por defecto = pausa
		temp_octave = octave;       // Seteo la octava a la por defecto de la canci?n
		temp_duration = duration;   // Seteo la duraci?n a la por defecto de la canci?n
		dot_flag = 0;               // Borro el flag de detecci?n de punto
		// Busco un prefijo de duraci?n
		if (*song>='0' && *song<='9')
		{
			temp_duration = *song - '0';
			song++;
			if (*song>='0' && *song<='9')
			{
				temp_duration = temp_duration*10 + (*song - '0');
				song++;
			}
		}
		// Busco una nota
		switch (*song)
		{
			case 'c': current_note = 0; break;    // C (do)
			case 'd': current_note = 2; break;    // D (re)
			case 'e': current_note = 4; break;    // E (mi)
			case 'f': current_note = 5; break;    // F (fa)
			case 'g': current_note = 7; break;    // G (sol)
			case 'a': current_note = 9; break;    // A (la)
			case 'b': current_note = 11; break;   // B (si)
			case 'p': current_note = 255; break;  // pausa
		}
		song++;                     // Avanzo al pr?ximo caracter
		// Busco un '#' siguiendo la nota
		if (*song=='#')
		{
			current_note++;   // Incremento la nota (A->A#, C->C#, D->D#, F->F#, G->G#)
			song++;                   // Avanzo al pr?ximo caracter
		}

		// Busco '.' (extiende la duraci?n de la nota un 50%)
		if (*song=='.')
		{
			dot_flag = 1;             // Si se encuentra '.', seteo el flag
			song++;                   // Avanzo al pr?ximo caracter
		}
		// Busco un sufijo de una octava
		if (*song>='0' && *song<='9')
		{
			temp_octave = *song - '0';// Seteo la octava en consecuencia
			song++;                   // Avanzo al pr?ximo caracter
		}
		if (*song=='.') // Un punto puede ser encontrado incluso despu?s de una octava
		{
			dot_flag = 1;             // Si se encuentra '.', seteo el flag
			song++;                   // Avanzo al pr?ximo caracter
		}
		while (*song == ',') song++;    // Salteo ','
		// Calculo la duraci?n de la nota
		calc_duration = (60000/tempo)/(temp_duration);
		calc_duration *= 4;         // La nota completa tiene cuatro beats
		// Chequeo si el flag de punto est? activado, de ser as?, extiendo la duraci?n en un 50%
		if (dot_flag) calc_duration = (calc_duration*3)/2;
		// Si la nota actual NO es una pausa, reproduzco la nota usando la funci?n sound
		if (current_note<255) sound(note[temp_octave-4][current_note],calc_duration);
		else
		{ // Si la nota actual es una pausa (255), espero dicha cantidad de tiempo
			duration_timer = calc_duration;
			sound_playing = 1;
		}
		while (sound_playing);      // Espero a la que nota/pausa en curso finalice
	}
	else {
		is_song_playing = 0;
	}
}

/* -------------------- GETTERS & SETTERS -------------------- */

void set_song(uint8_t song_num) {
	current_song = song_num;
	song = rtttl_library[current_song];
}

void set_duration_timer(int duration) {
	duration_timer = duration;
}

void set_sound_playing(unsigned int sound_playing_num) {
	sound_playing = sound_playing_num;
}

void set_duration(unsigned char duration_num) {
	duration = duration_num;
}

void set_octave(unsigned char octave_num) {
	octave = octave_num;
}

void set_tempo(unsigned int tempo_num) {
	tempo = tempo_num;
}

int get_duration_timer() {
	return duration_timer;
}

unsigned char get_duration() {
	return duration;
}

unsigned char get_octave() {
	return octave;
}

unsigned int get_tempo() {
	return tempo;
}

unsigned char get_is_song_playing(){
	return is_song_playing;
}

char* get_song_playing() {
	return (PGM_P)pgm_read_word(&(songs_menu[current_song]));
}

