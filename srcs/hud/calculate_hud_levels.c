#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void		check_level_limits(t_doom *doom)
{
	if (doom->hud->corona_level >= 100)
		doom->menu->game_over = TRUE;
	if (doom->hud->corona_level < 0)
		doom->hud->corona_level = 0;
	if (doom->hud->sanitizer_level >= 100)
		doom->hud->sanitizer_level = 100;
	if (doom->hud->sanitizer_level < 0)
		doom->hud->sanitizer_level = 0;
}

static int		update_hud_levels_3(t_doom *doom)
{
	int change;

	change = -1;
	if (doom->hud->corona == TRUE)
	{
		doom->hud->corona_level += 8;
		doom->hud->corona = FALSE;
		change = 1;
	}
	else if (doom->hud->boxes == TRUE)
	{
		doom->hud->corona_level += 2;
		doom->hud->boxes = FALSE;
		change = 1;
	}
	return (change);
}

static int		update_hud_levels_2(t_doom *doom)
{
	int change;

	change = -1;
	if (doom->hud->health_pack == TRUE)
	{
		doom->hud->corona_level -= 2;
		doom->hud->health_pack = FALSE;
		change = 1;
	}
	else if (doom->hud->shopper == TRUE)
	{
		doom->hud->corona_level += 5;
		doom->hud->shopper = FALSE;
		change = 1;
	}
	else if (doom->hud->health_pack_plus == TRUE)
	{
		doom->hud->corona_level -= 10;
		doom->hud->health_pack_plus = FALSE;
		change = 1;
	}
	else
		change = update_hud_levels_3(doom);
	return (change);
}

int			calculate_hud_levels(t_doom *doom)
{
	int change;

	change = -1;
	if (doom->hud->sanitizer == TRUE)
	{
		doom->hud->sanitizer_level += 15;
		doom->hud->sanitizer = FALSE;
		change = 1;
	}
	else if (doom->hud->sanitizer_shooting == TRUE)
	{
		doom->hud->sanitizer_level -= 5;
		doom->hud->sanitizer_shooting = FALSE;
		change = 1;
	}
	else if (doom->hud->facemask == TRUE)
	{
		doom->hud->corona_level -= 8;
		doom->hud->facemask = FALSE;
		change = 1;
	}
	else
		change = update_hud_levels_2(doom);
	check_level_limits(doom);
	return (change);
}
