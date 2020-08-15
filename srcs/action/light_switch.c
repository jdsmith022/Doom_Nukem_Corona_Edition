#include "../../includes/doom.h"
#include "../../includes/action.h"

static void		light_timer(t_doom *doom, bool *flag)
{
	int diff;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->own_event.light_time);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom);
		if (diff > 5)
		{
			doom->own_event.light_switch = FALSE;
			doom->lib.sector[doom->i_sector].light_level = \
				doom->own_event.hold_light;
		}
	}
}

static void		change_sector_light(t_doom *doom)
{
	t_sector sector;

	sector = doom->lib.sector[doom->i_sector];
	doom->own_event.hold_light = sector.light_level;
	if (sector.light_level > 10)
		sector.light_level = 10;
	else
		sector.light_level = 10;
}

static void		check_poster_location(t_doom *doom)
{
	t_sidedef poster;

	poster = doom->lib.sidedef[doom->i_sidedef];
	if (poster.action == 5)
	{
		doom->own_event.light_switch = TRUE;
		doom->own_event.light_timer = TRUE;
	}
}

void			light_switch(t_doom *doom)
{
	check_poster_location(doom);
	if (doom->own_event.light_switch == TRUE)
	{
		change_sector_light(doom);
		light_timer(doom, &doom->own_event.light_timer);
	}
}
