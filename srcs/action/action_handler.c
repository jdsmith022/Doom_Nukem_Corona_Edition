#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void	check_virus_select(t_doom *doom)
{
	    t_ray   ray;

    ray = init_ray(doom, MOUSE_X);
    check_hit(doom, ray, doom->i_sector, doom->i_sector);
	if (doom->own_event.virus_hit_index != -1)
		doom->hud->corona = TRUE;
}

void	action_handler(t_doom *doom)
{
	light_switch(doom);
	sliding_door(doom, -1);
	if (doom->own_event.select == TRUE)
	{
		if (MOUSE_PRESSED)
		{
			check_virus_select(doom); //check for tp in here too!!!
			sanitizer_refill(doom);
			doom->own_event.mouse_press = FALSE;
		}
	}
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		if (MOUSE_PRESSED)
		{
			doom->hud->sanitizer_shooting = TRUE;
			doom->own_event.mist = TRUE;
			shooting(doom);
		}
	}
}
