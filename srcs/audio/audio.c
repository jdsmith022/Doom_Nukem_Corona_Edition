#include "../../includes/doom.h" 
#include "../../includes/audio.h"

void	play_movement_sounds(t_audio *audio, t_event *event)
{
	if (event->jump == FALSE)
		audio->event->jump_toggled = FALSE;
	if (event->cam_move_f || event->cam_move_b)
		loop_sound(audio->sounds[FOOTSTEPS], 1);
	else
		pause_sound(audio->sounds[FOOTSTEPS], 1);
	if (event->cam_move_l || event->cam_move_r)
		loop_sound(audio->sounds[FOOTSTEPS], 1);
	if (event->jump && !audio->event->jump_toggled){
		pause_sound(audio->sounds[FOOTSTEPS], 1);
		play_sound(audio->sounds[JUMP], 2);
		audio->event->jump_toggled = TRUE;
	}
}

void	play_action_sounds(t_audio *audio, t_event *event)
{
	if (event->shoot)
		play_sound(audio->sounds[GUNSHOT], 2);
}

void	audio(t_audio *audio, t_event *event)
{
	if (audio->engine == OFF)
		return ;
	if (audio->music_vol)
		play_music(audio->music[0]);
	if (audio->sound_vol){
		play_movement_sounds(audio, event);
		play_action_sounds(audio, event);
	}
}
