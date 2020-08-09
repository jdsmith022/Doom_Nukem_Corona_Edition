#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void		update_hud_levels_2(t_doom *doom)
{
	if (doom->hud->health_pack == TRUE)
	{
		doom->hud->corona_level -= 5;
		doom->hud->health_pack = FALSE;
	}
	else if (doom->hud->shopper == TRUE)
	{
		doom->hud->corona_level += 10;
		doom->hud->shopper = FALSE;
	}
	else if (doom->hud->health_pack_plus == TRUE)
	{
		doom->hud->corona_level -= 15;
		doom->hud->health_pack_plus = FALSE;
	}
	else if (doom->hud->corona == TRUE)
	{
		doom->hud->corona_level += 15;
		doom->hud->corona = FALSE;
		if (doom->hud->corona_level >= 100)
			doom->menu->game_over = TRUE;
	}
}

void		calculate_hud_levels(t_doom *doom)
{
	int change;

	change = -1;
	if (doom->hud->sanitizer == TRUE)
	{
		doom->hud->sanitizer_level += 20;
		doom->hud->sanitizer = FALSE;
	}
	else if (doom->hud->sanitizer_shooting == TRUE)
	{
		doom->hud->sanitizer_level -= 5;
		doom->hud->sanitizer_shooting = FALSE;
	}
	else if (doom->hud->facemask == TRUE)
	{
		doom->hud->corona_level -= 10;
		doom->hud->facemask = FALSE;
	}
	else
		update_hud_levels_2(doom);
}
