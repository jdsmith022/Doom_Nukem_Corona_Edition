/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/07 16:54:08 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "../SDL2_mixer/SDL_mixer.h"

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"

#define AUDIO_BUFF 1042
#define NUM_OF_SOUNDS 3

#define AUDIO_PATH		"/Users/elkanfrank/dev/codam/doom_corona/sounds"

#define S_UI_1 			"/General Sounds/Buttons/sfx_sounds_button1.wav"
#define S_FOOTSTEPS 	"/Movement/Footsteps/sfx_movement_footstepsloop4_slow.wav"
#define S_JUMP			"/Movement/Jumping and Landing/sfx_movement_jump15.wav"
#define MU_1			"/music/main_theme.wav"

typedef struct		s_audio {
	int 			sample_rate;
	int				channels;
	uint16_t		format;
	Mix_Chunk		*sounds[NUM_OF_SOUNDS];
	Mix_Music		*music;
}					t_audio;

void				exit_error(const char *message);
void				init_audio();
void				load_audio(t_audio *audio);
void				play_music(Mix_Music *music);
void				play_sound(Mix_Chunk *sample, int channel);
void				loop_sound(Mix_Chunk *sample, int channel);
void				pause_sound(Mix_Chunk *sample, int channel);

#endif
