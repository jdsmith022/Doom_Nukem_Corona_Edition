#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"

void	play_movement_sounds(t_audio *audio, t_event *event)
{
	if (event->jump == FALSE)
		audio->event->jump_toggled = FALSE;
	if ((event->move_pos_f || event->move_pos_b) && \
		!event->jump && event->set_step)
	{
		loop_sound(audio->sounds[FOOTSTEPS], 1);
		event->set_step = FALSE;
	}
	else
		pause_sound(audio->sounds[FOOTSTEPS], 1);
	if ((event->move_pos_l || event->move_pos_r) && \
		!event->jump && event->set_step)
	{
		loop_sound(audio->sounds[FOOTSTEPS], 1);
		event->set_step = FALSE;
	}
	if (event->jump && !audio->event->jump_toggled)
	{
		pause_sound(audio->sounds[FOOTSTEPS], 1);
		play_sound(audio->sounds[JUMP], 2);
		audio->event->jump_toggled = TRUE;
	}
}

void	play_action_sounds(t_audio *audio, t_event *event)
{
	if (event->shoot && event->mouse_press)
		play_sound(audio->sounds[GUNSHOT], 2);
	if (event->fall && !event->died)
	{
		play_sound(audio->sounds[SCREAM], 2);
		event->died = TRUE;
	}
	if (event->groc_pickup)
	{
		play_sound(audio->sounds[HIT], 2);
		event->groc_pickup = FALSE;
	}
}

void	audio(t_doom *doom, t_event *event)
{
	if (doom->audio->engine == OFF)
		return ;
	if (AUDIO->music_vol && doom->is_running)
		play_music(AUDIO->music[1]);
	if (doom->audio->sound_vol)
	{
		play_movement_sounds(AUDIO, event);
		play_action_sounds(AUDIO, event);
	}
}
