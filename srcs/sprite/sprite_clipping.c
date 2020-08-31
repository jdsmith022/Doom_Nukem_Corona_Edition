/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/31 12:13:43 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	int		i;
	int		y_bottom;
	// int		y_top;
	int		mid_bottom;
	int		mid_top;

	mid_top = 0;
	mid_bottom = 0;
	i = 0;
	while (i < sprite.n_sector)
	{
		mid_bottom =\
		doom->lib.sector[sprite.prev_sectors[i]].mid_bottom[x];
		mid_top =\
		doom->lib.sector[sprite.prev_sectors[i]].mid_top[x];
		if (mid_bottom == -1)
			return (-1);
		if (mid_top == -1)
			return (-1);
		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].bottom[x];
		if (y_bottom > 0 && y_bottom < HEIGHT && y_bottom < screen_y)
			return (-1);
		if (mid_bottom > 0 && mid_bottom < HEIGHT && mid_bottom < screen_y)
			return (-1);
		if (mid_top > 0 && mid_top < HEIGHT && mid_top > screen_y)
			return (-1);
		i++;
	}
	return (1);
}
