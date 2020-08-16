#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

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
