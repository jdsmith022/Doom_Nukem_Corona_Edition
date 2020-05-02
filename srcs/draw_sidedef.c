/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/02 16:56:28 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, Uint32 color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = color;
}

void		draw_portal_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	Uint32	color;
	Uint32	*pixels;
	int		y;

	y = plane.sidedef_top;
	sidedef.action = 0;
	pixels = doom->surface->pixels;
	while (y <= plane.sidedef_bottom)
	{
		if (y < plane.mid_texture_bottom)
			color = pixels[(y * WIDTH) + x];
		if (y >= plane.mid_texture_bottom && y <= plane.mid_texture_bottom + 2)
			color = 0x000000;
		else if (y > plane.mid_texture_bottom + 2)
			color = 0x8b0000;
		put_pixel(doom, x, y, color);
		y++;
	}
}

static void		put_text(t_doom *doom, int x, int y, size_t index, Uint32 pixel_dex)
{
	char *pixels;
	char *text;

	(void)index;
	pixels = doom->surface->pixels;
	text = doom->textures[0]->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixels[index] = text[pixel_dex];
		index++;
		pixel_dex++;
		pixels[index] = text[pixel_dex];
		index++;
		pixel_dex++;
		pixels[index] = text[pixel_dex];
	}
}

void		draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	int			y;
	Uint32	pixel_dex;
	int			bpp;
	size_t	index;
	double	wall_y;

	(void)sidedef;
	y = plane.sidedef_top;
	bpp = doom->surface->format->BytesPerPixel;

	while (y <= plane.sidedef_bottom)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		wall_y = (double)(doom->wall_height / plane.sidedef_height) * (y - plane.sidedef_top);
		pixel_dex = (wall_y * doom->textures[0]->pitch) + ((int)sidedef.offset_x * doom->textures[0]->format->BytesPerPixel);
		put_text(doom, x, y, index, pixel_dex);
		y++;
	}
}

// void		draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
// {
// 	int		y;
// 	int		color;

// 	y = plane.sidedef_top;
// 	color = 0xdcedc1;
// 		printf("x: %d\n", x);
// 		printf("y: %d\n", y);
// 	while (y <= plane.sidedef_bottom)
// 	{
// 		if (sidedef.sector == 5)
// 			color = 0xdcedc1;
// 		else
// 			color = 0x088da5;
// 		put_pixel(doom, x, y, color);
// 		y++;
// 	}
// }
