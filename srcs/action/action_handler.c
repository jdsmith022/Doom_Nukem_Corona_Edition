#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

void	action_handler(t_doom *doom)
{
	sliding_door(doom, -1);
	if (doom->own_event.select == TRUE)
		light_switch(doom);
	if (doom->own_event.shoot == TRUE && doom->hud->sanitizer_level > 0)
	{
		doom->hud->sanitizer_shooting = TRUE;
		doom->own_event.mist = TRUE;
		shooting(doom);
	}
}
