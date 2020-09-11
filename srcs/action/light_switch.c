/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_switch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:17:50 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 13:38:09 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"

void			light_timer(t_doom *doom, int *flag)
{
	int diff;
	int	sector;

	if (*flag == light)
	{
		clock_gettime(doom->game.play_time, &doom->own_event.light_time);
		*flag = set;
		doom->lib.sidedef[doom->i_sidedef].txt_2 = 86;
	}
	else
	{
		sector = doom->own_event.hold_light_sector;
		diff = find_time_difference(doom, doom->own_event.light_time.tv_sec);
		if (diff > 3)
		{
			doom->own_event.light_switch = FALSE;
			doom->own_event.click_light = -1;
			doom->lib.sector[sector].light_level = \
				doom->own_event.hold_light;
			doom->lib.sidedef[doom->i_sidedef].txt_2 = 85;
			doom->own_event.light_switch_changed = TRUE;
		}
	}
}

void			change_sector_light(t_doom *doom)
{
	t_sector	*sector;
	int			id;

	id = doom->lib.sidedef[doom->i_sidedef].sector;
	sector = &doom->lib.sector[id];
	doom->own_event.hold_light = sector->light_level;
	doom->own_event.hold_light_sector = sector->id;
	if (sector->light_level < 1.0)
		sector->light_level = 1.0;
	else
		sector->light_level = 0.5;
	doom->own_event.click_light = 1;
}

static void		check_poster_location(t_doom *doom, t_sidedef poster)
{
	doom->own_event.light_switch = TRUE;
	doom->own_event.sd_action = light;
	doom->own_event.mouse_press = FALSE;
	doom->own_event.light_switch_changed = TRUE;
}

void			light_switch(t_doom *doom, t_sidedef poster)
{
	if (doom->own_event.light_switch == FALSE && poster.distance < 40.0)
		check_poster_location(doom, poster);
}
