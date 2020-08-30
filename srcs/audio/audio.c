#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"
#include "../../includes/audio.h"

static void	play_scissor_sounds(t_audio *audio, t_event *event)
{
	if (event->scissor_lift != audio->event->prev_scissor_state)
	{
		if (event->scissor_lift)
			loop_sound(audio->sounds[ENGINE], 4);
		else
			pause_sound(audio->sounds[ENGINE], 4);
		audio->event->prev_scissor_state = event->scissor_lift;
	}
	if (event->scissor_lift_up)
		play_sound(audio->sounds[LIFT_UP], -1);
	else if (event->scissor_lift_down)
		play_sound(audio->sounds[LIFT_DOWN], -1);
}

static void	play_movement_sounds(t_audio *audio, t_event *event)
{
	if (event->jump == FALSE)
		audio->event->jump_toggled = FALSE;
	if ((event->move_pos_f || event->move_pos_b) &&
		!event->jump && event->set_step)
	{
		loop_sound(audio->sounds[FOOTSTEPS], 6);
		event->set_step = FALSE;
	}
	else
		pause_sound(audio->sounds[FOOTSTEPS], 6);
	if ((event->move_pos_l || event->move_pos_r) &&
		!event->jump && event->set_step)
	{
		loop_sound(audio->sounds[FOOTSTEPS], 6);
		event->set_step = FALSE;
	}
	if (event->jump && !audio->event->jump_toggled)
	{
		pause_sound(audio->sounds[FOOTSTEPS], 6);
		play_sound(audio->sounds[JUMP], 2);
		audio->event->jump_toggled = TRUE;
	}
}

static void	play_action_sounds(t_doom *doom, t_audio *audio, t_event *event)
{
	if (event->shoot && event->mouse_press)
		play_sound(audio->sounds[GUNSHOT], -1);
	if (event->fall && !audio->event->prev_fall_state)
	{
		play_sound(audio->sounds[SCREAM], -1);
		audio->event->prev_fall_state = TRUE;
	}
	if (event->groc_pickup)
	{
		play_sound(audio->sounds[HIT], -1); // change sound
		event->groc_pickup = FALSE;
	}
	if (event->light_switch_changed && doom->i_sidedef != -1)
	{
		play_sound(audio->sounds[CLICK], -1);
		event->light_switch_changed = FALSE;
	}
	if (!event->fall)
		audio->event->prev_fall_state = event->fall;
}

static void	play_combat_sounds(t_doom *doom, t_audio *audio, int state)
{
	if (state == corona_hit)
		play_sound(audio->sounds[HIT], -1);
	if (state == sanitizer && doom->i_sidedef != -1 \
	&& doom->hud->sanitizer_level < 100)
		play_sound(audio->sounds[PICKUP], -1);
}

void		audio(t_doom *doom, t_event *event)
{
	if (doom->audio->engine == OFF)
		return ;
	if (doom->audio->music_vol && doom->is_running)
		play_music(doom->audio->music[1]);
	if (doom->audio->sound_vol)
	{
		play_movement_sounds(doom->audio, event);
		play_action_sounds(doom, doom->audio, event);
		play_combat_sounds(doom, doom->audio, doom->hud->update);
		play_scissor_sounds(doom->audio, event);
	}
}
