#ifndef AUDIO_H
# define AUDIO_H

# include "../SDL2_mixer/SDL_mixer.h"

# include <limits.h>
# include <unistd.h>

#define AUDIO_BUFF 1042
#define AUDIO_PATH audio->path
#define NUM_OF_SOUNDS 3

#define OFF 0
#define ON 1

#define S_UI_1 			"/General Sounds/Buttons/sfx_sounds_button1.wav"
#define S_FOOTSTEPS 	"/Movement/Footsteps/sfx_movement_footstepsloop4_slow.wav"
#define S_JUMP			"/Movement/Jumping and Landing/sfx_movement_jump15.wav"
#define MU_1			"/music/main_theme.wav"

typedef struct		s_audio_event {
	bool			jump_toggled;
}					t_audio_event;

typedef struct		s_audio {
	bool			engine;
	char			*path;
	int 			sample_rate;
	int				channels;
	uint16_t		format;
	Mix_Chunk		*sounds[NUM_OF_SOUNDS];
	Mix_Music		*music;
	t_audio_event	*event;
	uint8_t			sound_vol;
	uint8_t			music_vol;
}					t_audio;

void				exit_error(const char *message);
void				init_audio();
void				load_audio(t_audio *audio);
void				play_music(Mix_Music *music);
void				play_sound(Mix_Chunk *sample, int channel);
void				loop_sound(Mix_Chunk *sample, int channel);
void				pause_sound(Mix_Chunk *sample, int channel);

#endif
