#ifndef AUDIO_H
# define AUDIO_H

# include "../SDL2_mixer/SDL_mixer.h"

# include <limits.h>
# include <unistd.h>

#define AUDIO_BUFF 	1042
#define AUDIO		doom->audio
#define AUDIO_PATH 	audio->path
#define NUM_OF_SOUNDS 8

#define OFF 0
#define ON 1

#define BUTTON 		0
#define FOOTSTEPS 	1
#define JUMP		2
#define GUNSHOT		3
#define SCREAM		4
#define	HIT			5
#define	PICKUP		6
#define FINISH		7
#define THEME		8
#define BOSSA		9

#define S_UI_1 		"/General Sounds/Buttons/sfx_sounds_button1.wav"
#define S_FOOTSTEPS "/Movement/Footsteps/sfx_movement_footstepsloop4_slow.wav"
#define S_JUMP		"/Movement/Jumping and Landing/sfx_movement_jump4.wav"
#define S_GUNSHOT	"/Weapons/Single Shot Sounds/sfx_weapon_singleshot14.wav"
#define S_DEATH		"/Death Screams/Human/sfx_deathscream_human4.wav"
#define S_FALL		"/Movement/Falling Sounds/sfx_sounds_falling1.wav"
#define MU_1		"/music/main_theme.wav"
#define MU_2		"/music/supermarket_badspeakers.wav"

static const char *AUDIO_PATHS[] = {
	S_UI_1, S_FOOTSTEPS, S_JUMP,
	S_GUNSHOT, S_DEATH, S_FALL,
	MU_1, MU_2
};

typedef struct s_event	t_event;
typedef struct s_doom	t_doom;

typedef struct			s_audio_event {
	bool				jump_toggled;
	bool				groc_pickup;
}						t_audio_event;

typedef struct			s_audio {
	bool				engine;
	char				*path;
	int 				sample_rate;
	int					channels;
	uint16_t			format;
	Mix_Chunk			*sounds[NUM_OF_SOUNDS];
	Mix_Music			*music[2];
	t_audio_event		*event;
	uint8_t				sound_vol;
	uint8_t				music_vol;
}						t_audio;

void					audio(t_doom *doom, t_event *event);
void					exit_error(const char *message);
void					init_audio(t_doom *doom);
void					play_music(Mix_Music *music);
void					resume_music();
void					play_sound(Mix_Chunk *sample, int channel);
void					loop_sound(Mix_Chunk *sample, int channel);
void					pause_sound(Mix_Chunk *sample, int channel);

#endif
