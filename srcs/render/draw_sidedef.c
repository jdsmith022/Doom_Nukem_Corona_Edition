/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/30 09:22:18 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

// static void		put_dimishing_light(Uint32 *color, double dist)
// {
// 	*color = ((*color & 0xff) >> 24) * (int)dist << 24;
// 	*color = ((*color & 0x00ff) >> 16) * (int)dist << 16;
// 	*color = ((*color & 0x0000ff) >> 8) * (int)dist << 8;
// }

static void		put_texture(t_doom *doom, t_point pixel, Uint32 index,
					Uint32 pixel_dex)
{
	char *pixels;
	char *texture;

	pixels = doom->surface->pixels;
	texture = doom->textures[1]->pixels;
	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
	{
		pixels[index] = texture[pixel_dex];
		index++;
		pixel_dex++;
		pixels[index] = texture[pixel_dex];
		index++;
		pixel_dex++;
		pixels[index] = texture[pixel_dex];
	}
}

static void		put_protal_pixel(t_doom *doom, t_point pixel)
{
	Uint32 *pixels;
	Uint32	color;

	pixels = doom->surface->pixels;
	color = pixels[((int)pixel.y * WIDTH) + (int)pixel.x];
	pixels = doom->surface->pixels;
	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
		pixels[((int)pixel.y * WIDTH) + (int)pixel.x] = color;
}

static void		find_texture_index(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
	Uint32	pixel_dex;
	Uint32	index;
	double	wall_y;
	int		bpp;

	bpp = doom->surface->format->BytesPerPixel;
	index = (pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->wall_height_std / plane.height_standard) * ((int)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	bpp = doom->textures[1]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->textures[1]->pitch) + ((int)sidedef.offset * bpp);
	put_texture(doom, pixel, index, pixel_dex);
	//put_dimishing_lighting(&texure[pixel_dex], sidedef.distance)
}

void			draw_portal_sidedef(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	Uint32	*pixels;
	t_point	pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	pixels = doom->surface->pixels;
	while (pixel.y <= plane.sidedef_bottom)
	{
		if (pixel.y < plane.mid_texture_bottom)
			put_protal_pixel(doom, pixel);
		if (pixel.y > plane.mid_texture_bottom)
			find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}

void				draw_onesided_sidedef(t_doom *doom, t_plane plane,
							t_sidedef sidedef, int x)
{
	t_point	pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	while (pixel.y <= plane.sidedef_bottom)
	{
		find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}



// void		put_pixel(t_doom *doom, int x, int y, int color)
// {
// 	Uint32 *pixels;

// 	pixels = doom->surface->pixels;
// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 		pixels[(y * WIDTH) + x] = (Uint32)color;
// }

// void		draw_portal_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
// {
// 	int y;
// 	Uint32 color;
// 	Uint32 *pixels;

// 	y = plane.sidedef_top;
// 	sidedef.action = 0;
// 	pixels = doom->surface->pixels;
// 	while (y <= plane.sidedef_bottom)
// 	{
// 		if (y < plane.mid_texture_bottom)
// 			color = pixels[(y * WIDTH) + x];
// 		if (y >= plane.mid_texture_bottom && y <= plane.mid_texture_bottom + 2)
// 			color = 0x000000;
// 		else if (y > plane.mid_texture_bottom + 2)
// 			color = 0x8b0000;
// 		put_pixel(doom, x, y, color);
// 		y++;
// 	}
// }

// void		draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
// {
// 	int		y;
// 	int		color;

// 	y = plane.sidedef_top;
// 	color = 0xdcedc1;
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
