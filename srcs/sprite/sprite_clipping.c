/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/05 13:19:02 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		check_y_side_line(t_line line, int x, int y)
{
	t_point		compare;
	int			diff;
	int			diff_compare;

	compare.x = line.start.x;
	compare.y = line.start.y + 1;
	//if it is under the line return -1
	//if it is above the line return 1
	diff = (x - line.start.x) * (line.end.y - line.start.y) -\
			(y - line.start.y) * (line.end.x - line.start.x);
	diff_compare = (compare.x - line.start.x) * (line.end.y - line.start.y) -\
					(compare.y - line.start.y) * (line.end.x - line.start.x);
	if ((diff < 0 && diff_compare < 0) || (diff > 0 && diff_compare > 0)\
		|| diff == 0)
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

int		check_sector_values(t_sprite sprite, int id)
{
	int		i;

	i = 0;
	while (i < sprite.n_sector)
	{
		if (sprite.prev_sectors[i] == id)
			return (1);
		i++;
	}
	return (-1);
}

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	t_clip	*node;

	//mid_bottom
	node = doom->clip->head_mid_bottom->next;
	//loop through mid_bottom_lines
		//if sidedef_id corresponds with one of the sector id's in prev_sector
	while (node != NULL)
	{
		// if (sprite.sector == 36)
			// printf("test1\n");
		if (check_sector_values(sprite, node->id) == 1)
		{
			// if (sprite.sector == 36)
				// printf("test2\n");
			if (check_y_side_line(node->line, x, screen_y) == -1)
			{
				// if (sprite.sector == 36)
					// printf("test2\n");
				return (-1);
			}
		}
		node = node->next;
	}
	return (1);
}

// int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
// {
// 	int		i;
// 	t_line	y_bottom;
// 	t_line	mid_bottom;
// 	int		return_value;

// 	i = 0;
// 	return_value = 1;
// 	while (i < sprite.n_sector)
// 	{
// 		mid_bottom =\
// 		doom->lib.sector[sprite.prev_sectors[i]].mid_bottom;
// 		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].bottom;
// 		// do you want it neg of pos from this line?
// 		if (mid_bottom.start.x != -1)
// 		{
// 			if (mid_bottom.start.x > 0 && mid_bottom.start.x < WIDTH &&\
// 				mid_bottom.start.y > 0 && mid_bottom.start.y < HEIGHT)
// 			{
// 				if (sprite.action == 14 && sprite.sector == 11)
// 				{
// 					printf("IF1\nline: (%f;%f) - (%f;%f) ", mid_bottom.start.x, mid_bottom.start.y, mid_bottom.end.x, mid_bottom.end.y);
// 					printf("coord: (%d;%d)\n", x, screen_y);
// 				}
// 				if (x < mid_bottom.start.x)
// 					return_value = 1;
// 			}
// 			if (mid_bottom.end.x > 0 && mid_bottom.end.x < WIDTH &&\
// 				mid_bottom.end.y > 0 && mid_bottom.end.y < HEIGHT)
// 			{
// 				if (sprite.action == 14 && sprite.sector == 11)
// 				{
// 					printf("IF 2\nline: (%f;%f) - (%f;%f) ", mid_bottom.start.x, mid_bottom.start.y, mid_bottom.end.x, mid_bottom.end.y);
// 					printf("coord: (%d;%d)\n", x, screen_y);
// 				}
// 				if (x > mid_bottom.end.x)
// 					return_value = 1;
// 			}
// 			if (sprite.action == 14 && sprite.sector == 11)
// 			{
// 				printf("AFTER line: (%f;%f) - (%f;%f) ", mid_bottom.start.x, mid_bottom.start.y, mid_bottom.end.x, mid_bottom.end.y);
// 				printf("coord: (%d;%d)\n", x, screen_y);
// 			}
// 			if (check_y_side_line(mid_bottom, x, screen_y) == -1)
// 			{
// 				// printf("return -1\n");
// 				return (-1);
// 			}
// 		}
// 		if (check_y_side_line(y_bottom, x, screen_y) == -1)
// 		{
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	return (return_value);
// }
