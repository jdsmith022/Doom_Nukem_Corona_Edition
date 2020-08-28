#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"

static void		shoot_action(t_doom *doom)
{
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		if (doom->own_event.mouse_press)
		{
			doom->hud->update = sanitizer_shooting;
			doom->own_event.mist = TRUE;
			check_sprite_hit(doom);
		}
	}
}

static void		select_action(t_doom *doom)
{
	t_sidedef poster;

	poster = doom->lib.sidedef[doom->i_sidedef];
	light_switch(doom);
	if (doom->own_event.select == TRUE)
	{
		if (doom->own_event.mouse_press)
		{
			check_sprite_hit(doom);
			if (poster.action == 8)
				sanitizer_refill(doom);
		}
	}
}

void			action_handler(t_doom *doom)
{
	select_action(doom);
	shoot_action(doom);
	if (doom->own_event.fall == TRUE)
		player_fall(doom);
	if (doom->own_event.virus_red_i != -1)
		remove_red_virus(doom);
	if (doom->own_event.sliding_door != -1)
		render_sliding_door(doom, \
			&doom->lib.sidedef[doom->own_event.sliding_door]);
}
