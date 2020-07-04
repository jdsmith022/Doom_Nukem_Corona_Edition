/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/04 16:11:47 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "../SDL2_mixer/SDL_mixer.h"

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"

#define AUDIO_BUFF 1042
#define NUM_OF_SOUNDS 2

#define AUDIO_PATH		"/Users/elkanfrank/dev/codam/sdl_audio/sounds/"

#define S_UI_1 			"General Sounds/Buttons/sfx_sounds_button1.wav"
#define S_FOOTSTEPS 	"Movement/Footsteps/sfx_movement_footstepsloop4_slow.wav"
#define MU_1			"music/main_theme.wav"

#define BMP_SMALL 		"/Users/elkanfrank/dev/codam/sdl_audio/bmp/test_img/small.bmp"
#define BMP_7X7 		"/Users/elkanfrank/dev/codam/sdl_audio/bmp/test_img/7x7.bmp"
#define BMP_BLUE 		"/Users/elkanfrank/dev/codam/sdl_audio/bmp/test_img/blue.bmp"
#define BMP_W3			"/Users/elkanfrank/dev/codam/sdl_audio/bmp/test_img/w3c_home.bmp"

typedef struct		s_audio {
	int 			sample_rate;
	int				channels;
	uint16_t		format;
	Mix_Chunk		*sounds[NUM_OF_SOUNDS];
	Mix_Music		*music;
}					t_audio;

void				exit_error(const char *message);

#endif
