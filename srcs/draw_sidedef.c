/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou          #+#    #+#                */
/*   Updated: 2020/04/03 22:45:17 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = (Uint32)color;
}

void		draw_floor(t_doom *doom, int sector, int x, int y)
{
	Uint32 	color;
	
	while (y < HEIGHT)
	{
		if (sector == 1)
			color = 0xffa500;
		else
			color = 0x8b0000;
		put_pixel(doom, x, y, color);
		y++;	
	}
}

void		draw_ceiling(t_doom *doom, int sidedef_top, int sector, int x)
{
	int y;

	y = 0;
	sector = 0;
	while (y < sidedef_top)
	{
		put_pixel(doom, x, y, 0x5B2C6F);
		y++;
	}
}

void		draw_portal_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	int y;
	Uint32 color;
	Uint32 *pixels;

	y = plane.sidedef_top;
	sidedef.action = 0;
	pixels = doom->surface->pixels;
	while (y <= plane.sidedef_bottom)
	{
		if (y < plane.mid_textur_bottom)
			color = pixels[(y * WIDTH) + x];
		if (y >= plane.mid_textur_bottom && y <= plane.mid_textur_bottom + 2)
			color = 0x000000;
		else if (y > plane.mid_textur_bottom + 2)
			color = 0xffa500;
		put_pixel(doom, x, y, color);
		y++;
	}
}

void		draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	int		y;
	int		color;

	y = plane.sidedef_top;
	color = 0xdcedc1;
	while (y <= plane.sidedef_bottom)
	{
		if (sidedef.sector == 0)
			color = 0xdcedc1;
		else
			color = 0x088da5;
		put_pixel(doom, x, y, color);
		y++;	
	}
}