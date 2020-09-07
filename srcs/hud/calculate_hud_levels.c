/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_hud_levels.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:54 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 13:33:34 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void		check_level_limits(t_doom *doom)
{
	if (doom->hud->corona_level >= 100)
		doom->menu->state = game_over;
	else if (doom->hud->corona_level < 0)
		doom->hud->corona_level = 0;
	if (doom->hud->sanitizer_level >= 100)
		doom->hud->sanitizer_level = 100;
	else if (doom->hud->sanitizer_level < 0)
		doom->hud->sanitizer_level = 0;
}

void			calculate_hud_levels(t_doom *doom)
{
	if (doom->hud->update == sanitizer)
		doom->hud->sanitizer_level += 10;
	else if (doom->hud->update == sanitizer_shooting)
		doom->hud->sanitizer_level -= 1;
	else if (doom->hud->update == facemask)
		doom->hud->corona_level -= 8;
	else if (doom->hud->update == health_pack)
		doom->hud->corona_level -= 4;
	else if (doom->hud->update == shopper_collision)
		doom->hud->corona_level += 2;
	else if (doom->hud->update == health_pack_plus)
	{
		if (doom->hud->corona_level >= 10)
			doom->hud->corona_level -= 10;
		else
			doom->hud->corona_level -= doom->hud->corona_level;
	}
	else if (doom->hud->update == corona_hit)
		doom->hud->corona_level += 4;
	else if (doom->hud->update == boxes)
		doom->hud->corona_level += 2;
	check_level_limits(doom);
	doom->hud->update = -1;
}
