/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/05 19:33:55 by rsteigen      ########   odam.nl         */
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

int		clip_top(t_doom *doom, int index_sp, int x, int screen_y)
{
	t_clip		*top;
	t_sprite	sprite;

	// printf("begin clip top\n");
	sprite = doom->lib.sprites[index_sp];
	// printf("clip top 1\n");
	if (doom->clip->head_top == NULL)
		return (-1);
	top = doom->clip->head_top->next;
	// printf("clip top 2\n");
	while (top != NULL)
	{
		// printf("clip top 3\n");
		if (check_sector_values(sprite, top->id) == 1)
		{
			// printf("clip top 4\n");
			if (x > top->line.start.x && x < top->line.end.x)
			{
				// printf("clip top 5\n");
				if (check_y_side_line(top->line, x, screen_y) == 1)
				{
					printf("clip top 5\n");
					return (1);
				}
			}
		}
		top = top->next;
	}
	return (-1);
}

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	t_clip	*mid_bottom;
	t_clip	*bottom;

	//mid_bottom
	// printf("no clip 1\n");
	mid_bottom = doom->clip->head_mid_bottom->next;
	// printf("no clip 1.1\n");
	bottom = doom->clip->head_bottom->next;
	// printf("no clip 1.2\n");
	while (mid_bottom != NULL)
	{
		if (check_sector_values(sprite, mid_bottom->id) == 1)
		{
			if (x > mid_bottom->line.start.x && x < mid_bottom->line.end.x)
			{
				if (check_y_side_line(mid_bottom->line, x, screen_y) == -1)
				{
					return (-1);
				}
			}
		}
		mid_bottom = mid_bottom->next;
	}
	// printf("no clip 2\n");
	//bottom
	while (bottom != NULL)
	{
		if (check_sector_values(sprite, bottom->id) == 1)
		{
			if (x > bottom->line.start.x && x < bottom->line.end.x)
			{
				if (check_y_side_line(bottom->line, x, screen_y) == -1)
				{
					return (-1);
				}
			}
		}
		bottom = bottom->next;
	}
	// printf("no clip end\n");
	return (1);
}
