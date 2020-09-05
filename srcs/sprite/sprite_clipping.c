/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/05 20:20:28 by rsteigen      ########   odam.nl         */
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

int		clip_top(t_doom *doom, int index_sp, int x, int screen_y)
{
	t_clip		*top;
	t_sprite	sprite;

	sprite = doom->lib.sprites[index_sp];
	top = doom->clip->head_top->next;
	while (top != NULL)
	{
		if (check_sector_values(sprite, top->id) == 1)
		{
			if (x > top->line.start.x && x < top->line.end.x)
			{
				if (check_y_side_line(top->line, x, screen_y) == 1)
					return (1);
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

	mid_bottom = doom->clip->head_mid_bottom->next;
	bottom = doom->clip->head_bottom->next;
	while (mid_bottom != NULL)
	{
		if (check_sector_values(sprite, mid_bottom->id) == 1)
		{
			if (x > mid_bottom->line.start.x && x < mid_bottom->line.end.x)
			{
				if (check_y_side_line(mid_bottom->line, x, screen_y) == -1)
					return (-1);
			}
		}
		mid_bottom = mid_bottom->next;
	}
	while (bottom != NULL)
	{
		if (check_sector_values(sprite, bottom->id) == 1)
		{
			if (x > bottom->line.start.x && x < bottom->line.end.x)
			{
				if (check_y_side_line(bottom->line, x, screen_y) == -1)
					return (-1);
			}
		}
		bottom = bottom->next;
	}
	return (1);
}
