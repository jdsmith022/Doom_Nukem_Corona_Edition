/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rgb_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 09:43:13 by jessicasmit    #+#    #+#                */
/*   Updated: 2020/02/02 09:57:23 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		set_color_to_end(t_color *color, t_events *events)
{
	if (events->color_set == 0)
	{
		color->start = ONE_MIDDLE;
		color->end = ONE_END;
	}
	else if (events->color_set == 1)
	{
		color->start = TWO_MIDDLE;
		color->end = TWO_END;
	}
	else if (events->color_set == 2)
	{
		color->start = THREE_MIDDLE;
		color->end = THREE_END;
	}
}

static void		set_color_to_mid(t_color *color, t_events *events)
{
	if (events->color_set == 0)
	{
		color->start = ONE_START;
		color->end = ONE_MIDDLE;
	}
	else if (events->color_set == 1)
	{
		color->start = TWO_START;
		color->end = TWO_MIDDLE;
	}
	else if (events->color_set == 2)
	{
		color->start = THREE_START;
		color->end = THREE_MIDDLE;
	}
}

int					rgb_color(t_mlx *mlx, double calc_nb)
{
	t_color color;
	double	percent;
	int		red;
	int		green;
	int		blue;

	percent = percentage(mlx, calc_nb);
	if (calc_nb <= mlx->min)
		set_color_to_mid(&mlx->color, mlx->events);
	else
		set_color_to_end(&mlx->color, mlx->events);
	color = mlx->color;
	red = get_bit_value(
		(color.start >> 16) & 0xFF, (color.end >> 16) & 0xFF, percent);
	green = get_bit_value(
		(color.start >> 8) & 0xFF, (color.end >> 8) & 0xFF, percent);
	blue = get_bit_value(color.start & 0xFF, color.end & 0xFF, percent);
	return (red << 16 | green << 8 | blue);
}
