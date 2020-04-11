/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/11 17:01:43 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include <stdio.h>

static void		put_text(t_doom *doom, int x, int y, size_t index, Uint8 *pixel_dex)
{
	Uint32 *pixels;
	Uint32 *text;

	pixels = doom->surface->pixels;
	text = doom->textures[0]->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixels[index] = pixel_dex[0];
		index++;
		pixels[index] = pixel_dex[1];
		index++;
		pixels[index] = pixel_dex[2];
	}

}

void		put_pixel(t_doom *doom, int x, int y, Uint32 color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = color;
}

void		draw_floor(t_doom *doom, int sector, int x, int y)
{
	Uint32	color;

	while (y < HEIGHT)
	{
		if (sector == 1)
			color = 0xffa500;
		else
			color = 0xffa500;
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

void		draw_portal_sidedef(t_doom *doom, t_plane plane,
				t_sidedef sidedef, int x)
{
	Uint32	color;
	Uint32	*pixels;
	int		y;

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
			color = 0x8b0000;
		put_pixel(doom, x, y, color);
		y++;
	}
}

void		draw_onesided_sidedef(t_doom *doom, t_plane plane,
				t_sidedef sidedef, int x)
{
	int		y;
	Uint8 *pixel_dex;
	int		bpp;
	size_t	index;
	Uint8	*pixels;

	(void)sidedef;
	y = plane.sidedef_top;
	pixels = doom->textures[0]->pixels;
	while (y <= plane.sidedef_bottom)
	{
		bpp = doom->textures[0]->format->BytesPerPixel;
		index = (y * doom->textures[0]->pitch) + (x * bpp / 8);
		printf("%zu\n", index);
		pixel_dex = (Uint8 *)(pixels + y * doom->textures[0]->pitch + (int)sidedef.offset_x * bpp / 8);
		// printf("%d\n", pixel_dex);
		put_text(doom, x, y, index, pixel_dex);
		y++;
	}
}

	// int		color;
	// color = 0xdcedc1;
		// if (sidedef.sector == 5)
		// 	color = 0xdcedc1;
		// else
		// 	color = 0x088da5;