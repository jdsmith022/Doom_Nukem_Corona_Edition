/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/31 13:12:27 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		clip_top(t_doom *doom, int index_sp, int x, int screen_y)
{
	int			mid_top;
	t_sprite	sprite;
	int			i;
	int			y_top;

	i = 0;
	sprite = doom->lib.sprites[index_sp];
	while (i < sprite.n_sector)
	{
		y_top = doom->lib.sector[sprite.prev_sectors[i]].top[x];
		mid_top =\
		doom->lib.sector[sprite.prev_sectors[i]].mid_top[x];
		if (mid_top == -1)
			return (1);
		if (mid_top > 0 && mid_top < HEIGHT && mid_top > screen_y)
			return (1);
		if (y_top > 0 && y_top < HEIGHT && y_top > screen_y)
			return (1);
		i++;
	}
	return (-1);
}

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	int		i;
	int		y_bottom;
	int		mid_bottom;

	mid_bottom = 0;
	i = 0;
	while (i < sprite.n_sector)
	{
		mid_bottom =\
		doom->lib.sector[sprite.prev_sectors[i]].mid_bottom[x];
		if (mid_bottom == -1)
			return (-1);
		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].bottom[x];
		if (y_bottom > 0 && y_bottom < HEIGHT && y_bottom < screen_y)
			return (-1);
		if (mid_bottom > 0 && mid_bottom < HEIGHT && mid_bottom < screen_y)
			return (-1);
		i++;
	}
	return (1);
}
