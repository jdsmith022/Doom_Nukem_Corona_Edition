/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/02 21:17:42 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		check_y_side_line(t_line line, int x, int y)
{
	t_point		compare;
	int			diff;
	int			diff_compare;

	compare.x = line.start.x;
	compare.y = line.start.y;
	//if it is under the line return -1
	//if it is above the line return 1
	diff = (x - line.start.x) * (line.end.y - line.start.y) -\
			(y - line.start.y) * (line.end.x - line.start.x);
	diff_compare = (x - line.start.x) * (line.end.y - line.start.y) -\
					(y - line.start.y) * (line.end.x - line.start.x);
	if ((diff < 0 && diff_compare < 0) || diff == 0)
		return (-1);
	else
		return (1);
}


// int		clip_top(t_doom *doom, int index_sp, int x, int screen_y)
// {
// 	int			mid_top;
// 	t_sprite	sprite;
// 	int			i;
// 	int			y_top;

// 	i = 0;
// 	sprite = doom->lib.sprites[index_sp];
// 	while (i < sprite.n_sector)
// 	{
// 		y_top = doom->lib.sector[sprite.prev_sectors[i]].top[x];
// 		mid_top =\
// 		doom->lib.sector[sprite.prev_sectors[i]].mid_top[x];
// 		if (mid_top == -1)
// 			return (1);
// 		if (y_top == -1)
// 			return (1);
// 		if (mid_top > 0 && mid_top < HEIGHT && mid_top > screen_y)
// 			return (1);
// 		if (y_top > 0 && y_top < HEIGHT && y_top > screen_y)
// 			return (1);
// 		i++;
// 	}
// 	return (-1);
// }

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	int		i;
	t_line	y_bottom;
	t_line	mid_bottom;

	i = 0;
	if ((sprite.action == 10 && sprite.sector == 35) || (sprite.action == 14 && sprite.sector == 48) || (sprite.action == 14 && sprite.sector == 49))
		printf("n_sector: %d\n", sprite.n_sector);
	while (i < sprite.n_sector)
	{
		mid_bottom =\
		doom->lib.sector[sprite.prev_sectors[i]].mid_bottom;
		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].bottom;
		if ((sprite.action == 10 && sprite.sector == 35) || (sprite.action == 14 && sprite.sector == 48) || (sprite.action == 14 && sprite.sector == 49))
		{
			printf("bottom %d: (%f;%f) (%f;%f)\n", i, mid_bottom.start.x, mid_bottom.start.y, mid_bottom.end.x, mid_bottom.end.y);
			printf("mid_bottom %d: (%f;%f) (%f;%f)\n", i, mid_bottom.start.x, mid_bottom.start.y, mid_bottom.end.x, mid_bottom.end.y);
		}
		//do you want it neg of pos from this line?
		// if (check_y_side_line(y_bottom, x, screen_y) == -1)
		// {
		// 	if ((sprite.action == 10 && sprite.sector == 35) || (sprite.action == 14 && sprite.sector == 48) || (sprite.action == 14 && sprite.sector == 49))
		// 		printf("(mid_bottom) check_y_side_line == -1\n");
		// 	return (-1);
		// }
		if (mid_bottom.start.x != -1 &&\
			check_y_side_line(mid_bottom, x, screen_y) == -1)
		{
			if ((sprite.action == 10 && sprite.sector == 35) || (sprite.action == 14 && sprite.sector == 48) || (sprite.action == 14 && sprite.sector == 49))
				printf("(mid_bottom) check_y_side_line == -1\n");
			return (-1);
		}
		i++;
	}
	return (1);
}
