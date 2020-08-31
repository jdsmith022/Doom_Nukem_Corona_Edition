/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_light.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:11 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/31 17:17:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	sprite_light(t_doom *doom, t_sprite sprite)
{
	int		half_width;
	int		half_height;
	int		x;

	half_width = 0;
	half_height = 0;
	x = sprite.sprite_x;
	if (doom->game.light == TRUE)
	{
		if (doom->lib.sector[sprite.sector].light == TRUE)
			doom->lib.light = doom->lib.sector[sprite.sector].light_level;
		else
			doom->lib.light = 0.15;
	}
	else
	{
		half_width = (float)WIDTH / 2;
		doom->lib.light = 1 / (sprite.distance / 70);
		if (sprite.sprite_x > half_width)
			doom->lib.light -= (x - half_width) * 1.0 / (float)WIDTH;
		else
		{
			doom->lib.light =\
			+doom->lib.light - (half_width - x) * 1.0 / (float)WIDTH;
		}	
	}
}