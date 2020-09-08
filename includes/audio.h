/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD
/*   Created: 2020/08/28 15:10:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:36:23 by elkanfrank    ########   odam.nl         */
=======
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:44:29 by JessicaSmit   ########   odam.nl         */
>>>>>>> JS_draw_img
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "../SDL2_mixer/SDL_mixer.h"

# include <limits.h>
# include <unistd.h>

# define AUDIO_BUFF		1042

# define OFF			0
# define ON				1

# define NUM_OF_SOUNDS	15
# define CHANNELS		8

# define BUTTON 		0
# define FOOTSTEPS 		1
# define JUMP			2
# define GUNSHOT		3
# define SCREAM			4
# define FALL			5
# define CLICK			6
# define POWERUP		7
# define PICKUP			8
# define HIT			9
# define ENGINE			10
# define LVL_FINISH		11
# define GAMEOVER		12
# define LIFT_UP		13
# define LIFT_DOWN		14

# define S_UI_1 		"/General Sounds/Buttons/sfx_sounds_button1.wav"
# define S_FOOTSTEPS 	"/Movement/Footsteps/footstep_loop.wav"
# define S_JUMP			"/Movement/Jumping and Landing/sfx_movement_jump4.wav"
# define S_GUNSHOT		"/Weapons/Single Shot Sounds/spray.wav"
# define S_DEATH		"/Death Screams/Human/sfx_deathscream_human4.wav"
# define S_FALL			"/Movement/Falling Sounds/sfx_sounds_falling1.wav"
# define S_CLICK		"/General Sounds/Buttons/lightswitch.wav"
# define S_POWERUP		"/General Sounds/Coins/powerup.wav"
# define S_PICKUP		"/General Sounds/Buttons/pickup_item.wav"
# define S_HIT			"/Weapons/Single Shot Sounds/singleshot11.wav"
# define S_ENGINE		"/General Sounds/Buttons/scissorlift_engine.wav"
# define S_CHECKOUT		"/General Sounds/Buttons/cash_register.wav"
# define S_GAMEOVER		"/General Sounds/Menu Sounds/game_over.wav"
# define S_LIFT_U		"/General Sounds/Buttons/scissorlift_updown.wav"
# define S_LIFT_D		"/General Sounds/Buttons/scissorlift_updown.wav"
# define MU_1			"/music/main_theme.wav"
# define MU_2			"/music/supermarket_badspeakers.wav"

static const char *g_audio_paths[] = {
	S_UI_1, S_FOOTSTEPS, S_JUMP,
	S_GUNSHOT, S_DEATH, S_FALL,
	S_CLICK, S_POWERUP, S_PICKUP, S_HIT, S_ENGINE,
	S_CHECKOUT, S_GAMEOVER, S_LIFT_U, S_LIFT_D,
	MU_1, MU_2
};

typedef struct s_event	t_event;
typedef struct s_doom	t_doom;

typedef struct			s_audio_event {
	bool				jump_toggled;
	bool				groc_pickup;
	bool				prev_scissor_state;
	bool				prev_fall_state;
}						t_audio_event;

typedef struct			s_audio {
	bool				engine;
	char				*path;
	int					sample_rate;
	int					channels;
	uint16_t			format;
	Mix_Chunk			*sounds[NUM_OF_SOUNDS];
	Mix_Music			*music[2];
	t_audio_event		*event;
	uint8_t				sound_vol;
	uint8_t				music_vol;
}						t_audio;

void					audio(t_doom *doom, t_event *event);
void					exit_error(t_doom *doom, const char *message);
void					play_music(Mix_Music *music);
void					resume_music();
void					play_sound(Mix_Chunk *sample, int channel);
void					loop_sound(Mix_Chunk *sample, int channel);
void					pause_sound(Mix_Chunk *sample, int channel);
void					stop_sounds(void);

#endif
