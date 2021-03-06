/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_clipping.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/07 13:01:53 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

static int		check_sector_values(t_sprite sprite, int id)
{
	int			i;

	i = 0;
	while (i < sprite.n_sector)
	{
		if (sprite.prev_sectors[i] == id)
			return (1);
		i++;
	}
	return (-1);
}

int				clip_top(t_doom *doom, int index_sp, int x, int screen_y)
{
	t_clip		*top;
	t_sprite	sprite;

	sprite = doom->lib.sprites[index_sp];
	top = doom->clip->head_top->next;
	while (top != NULL)
	{
		if (check_sector_values(sprite, top->sector_id) == 1)
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

static int		check_mid_bottom_lines(t_clip *mid_bottom, int x)
{
	if ((x >= mid_bottom->line.start.x && x <= mid_bottom->line.end.x) ||\
	(mid_bottom->line.start.y <= 15 && x <= mid_bottom->line.start.x) ||\
	(mid_bottom->line.end.y <= 15 && x >= mid_bottom->line.end.x))
		return (1);
	return (-1);
}

static int		bottom_clipping_region(t_clip *bottom, t_sprite sprite, int x,
					int screen_y)
{
	while (bottom != NULL)
	{
		if (check_sector_values(sprite, bottom->sector_id) == 1)
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

int				no_clipping_region(int screen_y, t_sprite sprite,\
				t_doom *doom, int x)
{
	t_clip	*mid_bottom;
	t_clip	*bottom;

	mid_bottom = doom->clip->head_mid_bottom->next;
	bottom = doom->clip->head_bottom->next;
	while (mid_bottom != NULL)
	{
		if (check_sector_values(sprite, mid_bottom->sector_id) == 1)
		{
			if (check_mid_bottom_lines(mid_bottom, x) == 1)
			{
				if (check_y_side_line(mid_bottom->line, x, screen_y) == -1)
					return (-1);
			}
		}
		mid_bottom = mid_bottom->next;
	}
	return (bottom_clipping_region(bottom, sprite, x, screen_y));
}
