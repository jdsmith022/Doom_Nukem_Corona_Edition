/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_light.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:11 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/06 23:51:06 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	sprite_light2(t_doom *doom, t_sprite sprite, int x, int y)
{
	double dist;

	dist = sprite.distance;
	doom->lib.light = 1.0 / ((float)sprite.distance / 70.0);
	if (x > WIDTH / 2)
		doom->lib.light -= \
			(x - (float)WIDTH / 2.0) * 1.0 / (float)WIDTH;
	else
		doom->lib.light = \
		+doom->lib.light - \
		((float)WIDTH / 2.0 - x) * 1.0 / (float)WIDTH;
	if (y > HEIGHT / 2)
		doom->lib.light -= \
		(y - (float)HEIGHT / 2.0) * 1.0 / (float)HEIGHT;
	else
		doom->lib.light = \
		+doom->lib.light - \
		((float)HEIGHT / 2.0 - y) * 1.0 / (float)HEIGHT;
	if (doom->lib.light < 0.01)
		doom->lib.light = 0.01;
}

void	sprite_light(t_doom *doom, t_sprite sprite, int y)
{
	int		half_width;
	int		x;

	half_width = 0;
	x = sprite.sprite_x;
	if (doom->game.light == TRUE || \
	doom->lib.sector[sprite.sector].action == OUTSIDE)
	{
		if (doom->lib.sector[sprite.sector].light == TRUE)
			doom->lib.light = doom->lib.sector[sprite.sector].light_level;
		else
			doom->lib.light = 0.15;
	}
	else
		sprite_light2(doom, sprite, x, y);
}
