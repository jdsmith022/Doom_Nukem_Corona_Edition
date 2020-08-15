#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

void	action_handler(t_doom *doom)
{
	sliding_door(doom, -1);
	light_switch(doom);
	if (doom->own_event.select == TRUE)
	{
		sanitizer_refill(doom);
	}
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		if (MOUSE_PRESSED)
		{
			doom->hud->sanitizer_shooting = TRUE;
			doom->own_event.mist = TRUE;
			shooting(doom);
			doom->own_event.mouse_press = FALSE;
		}
	}
}
