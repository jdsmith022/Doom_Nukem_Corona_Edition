#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void	shoot_action(t_doom *doom)
{
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		if (MOUSE_PRESSED)
		{
			doom->hud->sanitizer_shooting = TRUE;
			doom->own_event.mist = TRUE;
			check_sprite_hit(doom);
			doom->own_event.mouse_press = FALSE;
		}
		doom->own_event.mouse_press = FALSE;
	}
}

static void	select_action(t_doom *doom)
{
	t_sidedef poster;

	poster = doom->lib.sidedef[doom->i_sidedef];
	light_switch(doom);
	if (doom->own_event.select == TRUE)
	{
		if (MOUSE_PRESSED)
		{
			check_sprite_hit(doom);
			if (poster.action == 8)
				sanitizer_refill(doom);
			doom->own_event.mouse_press = FALSE;
		}
	}
}

void	action_handler(t_doom *doom)
{
	sliding_door(doom, -1);
	select_action(doom);
	shoot_action(doom);
	if (doom->own_event.fall == TRUE)
		player_fall(doom);
}
