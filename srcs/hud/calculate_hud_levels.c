#include "../../includes/doom.h"
#include "../../includes/hud.h"

static int		update_hud_levels_2(t_doom *doom)
{
	int change;

	change = -1;
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
	}
	if (doom->hud->health_pack == FALSE || doom->hud->shopper == FALSE || \
	doom->hud->health_pack_plus == FALSE || doom->hud->corona == FALSE)
		change = 1;
	return (change);
}

int		calculate_hud_levels(t_doom *doom)
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
	if (doom->hud->facemask == FALSE || \
	doom->hud->sanitizer_shooting == FALSE || doom->hud->sanitizer == FALSE)
		change = 1;
	else
		change = update_hud_levels_2(doom);
	return (change);
}
