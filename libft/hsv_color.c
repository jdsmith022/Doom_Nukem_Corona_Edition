/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hsv_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 09:32:04 by jessicasmit    #+#    #+#                */
/*   Updated: 2020/02/02 10:04:09 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <math.h>

static int	rgb(double r, double g, double b)
{
	r *= 255;
	g *= 255;
	b *= 255;
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

static int	hsv_to_rgb(double h, double s, double v)
{
	int			index;
	double		f;
	double		p;
	double		q;
	double		t;

	if (s == 0)
		return ((int)v | (int)v | (int)v);
	h /= 60;
	index = floor(h);
	f = h - index;
	p = v * (1.f - s);
	q = v * (1.f - s * f);
	t = v * (1.f - s * (1.f - f));
	if (index == 0)
		return (rgb(v, t, p));
	else if (index == 1)
		return (rgb(q, v, p));
	else if (index == 2)
		return (rgb(p, v, t));
	else if (index == 3)
		return (rgb(p, q, v));
	else if (index == 4)
		return (rgb(t, p, v));
	return (rgb(v, p, q));
}

int			hsv_color(double calc_nb)
{
	t_color		color;

	if (calc_nb < 40)
		color.hue = (int)((360 - 150) * (calc_nb / 40));
	else
		color.hue = (int)(360 * (calc_nb / 150));
	color.saturation = 1;
	color.value = 1;
	return (hsv_to_rgb(color.hue, color.saturation, color.value));
}
