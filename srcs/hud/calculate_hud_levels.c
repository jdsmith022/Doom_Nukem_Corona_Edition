#include "../../includes/doom.h"
#include "../../includes/hud.h"

static void		update_hud_levels_2(t_doom *doom)
{
	if (doom->hud->shopper == TRUE)
	{
		printf("shopper\n");
		doom->hud->corona_level += 10;
		doom->hud->shopper = FALSE;
	}
	else if (doom->hud->corona == TRUE)
	{
		doom->hud->corona_level += 15;
		printf("corona level: %d\n", doom->hud->corona_level);
		doom->hud->corona = FALSE;
	}
}

void		update_hud_levels(t_doom *doom)
{
	if (doom->hud->sanitizer == TRUE)
	{
		printf("sani\n");
		doom->hud->sanitizer_level += 10;
		doom->hud->sanitizer = FALSE;
	}
	else if (doom->hud->facemask == TRUE)
	{
		printf("facemask\n");
		doom->hud->corona_level -= 10;
		doom->hud->facemask = FALSE;
	}
	else if (doom->hud->health_pack == TRUE)
	{
		printf("health_pack\n");
		doom->hud->corona_level -= 5;
		doom->hud->health_pack = FALSE;
	}
	else if (doom->hud->health_pack_plus == TRUE)
	{
		printf("health_pack_plus\n");
		doom->hud->corona_level -= 15;
		doom->hud->health_pack_plus = FALSE;
	}
	else
		update_hud_levels_2(doom);
}
