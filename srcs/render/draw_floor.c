/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/16 18:12:55 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = (Uint32)color;
}

void		draw_ceiling(t_doom *doom, int x, int sidedef_top)
{
	int y;

	y = 0;
	while (y < sidedef_top)
	{
		put_pixel(doom, x, y, 0x5B2C6F);
		y++;
	}
}

void		draw_floor(t_doom *doom, int x, int y)
{
	Uint32	color;

	while (y < HEIGHT)
	{
		color = 0xffa500;
		put_pixel(doom, x, y, color);
		y++;
	}
}
