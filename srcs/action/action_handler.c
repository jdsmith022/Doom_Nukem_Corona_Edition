#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void	action_posters(t_doom *doom)
{
	t_sidedef poster;

	poster = doom->lib.sidedef[doom->i_sidedef];
	light_switch(doom);
	if (doom->own_event.select == TRUE)
	{
		if (MOUSE_PRESSED)
		{
			check_virus_select(doom); //check for tp in here too!!!
			if (poster.action == 8)
				sanitizer_refill(doom);
		}
		doom->own_event.mouse_press = FALSE;
	}

}

void	action_handler(t_doom *doom)
{
	t_point start;
	t_point end;

	start.x = WIDTH / 2;
	start.y = HEIGHT / 2;
	end.x = WIDTH / 2 + 16;
	end.y = HEIGHT / 2 + 16;
	sliding_door(doom, -1);
	action_posters(doom);
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		if (MOUSE_PRESSED)
		{
			doom->hud->sanitizer_shooting = TRUE;
			doom->own_event.mist = TRUE;
			shooting(doom);
		}
	}
	if (doom->own_event.fall == TRUE)
		player_fall(doom);
}
