#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
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
		play_sound(audio->sounds[GUNSHOT], -1);
	if (event->fall && !event->died)
	{
		play_sound(audio->sounds[SCREAM], -1);
		event->died = TRUE;
	}
	if (event->groc_pickup)
	{
		play_sound(audio->sounds[PICKUP], -1);
		event->groc_pickup = FALSE;
	}
	if (event->light_switch_changed)
	{
		play_sound(audio->sounds[CLICK], -1);
		event->light_switch_changed = FALSE;
	}
	if (event->corona_hit)
		play_sound(audio->sounds[HIT], -1);
}

void	audio(t_doom *doom, t_event *event)
{
	if (doom->audio->engine == OFF)
		return ;
	if (doom->audio->music_vol && doom->is_running)
		play_music(doom->audio->music[1]);
	if (doom->audio->sound_vol)
	{
		play_movement_sounds(doom->audio, event);
		play_action_sounds(doom->audio, event);
	}
}
