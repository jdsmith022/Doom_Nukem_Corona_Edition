/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/03 10:53:27 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		put_texture(t_doom *doom, t_point pixel, size_t index, 
					Uint32 pixel_dex, int tex_dex)
{
	char *pixels;
	char *text;

	pixels = doom->surface->pixels;
	text = doom->textures[tex_dex]->pixels;
	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
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
					t_sidedef sidedef, int tex_dex)
{
	Uint32	pixel_dex;
	int		bpp;
	size_t	index;
	double	wall_y;
	
	bpp = doom->surface->format->BytesPerPixel;
	index = (pixel.y * doom->surface->pitch) + (pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.sidedef_height)	* (pixel.y - plane.sidedef_top);
	bpp = doom->textures[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->textures[tex_dex]->pitch) + ((int)sidedef.offset * bpp);
	put_texture(doom, pixel, index, pixel_dex, tex_dex);
}

void			draw_portal_sidedef(t_doom *doom, t_plane plane, 
					t_sidedef sidedef, int x)
{
	Uint32	*pixels;
	// Uint32	color;
	t_point	pixel;
	int		tex_dex = 1;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	pixels = doom->surface->pixels;
	while (pixel.y <= plane.sidedef_bottom)
	{
		if (pixel.y < plane.mid_texture_bottom)
			put_protal_pixel(doom, pixel);
		// if (pixel.y >= plane.mid_texture_bottom && pixel.y <= plane.mid_texture_bottom + 2)
		// 	color = 0x000000;
		if (pixel.y > plane.mid_texture_bottom)
			find_texture_index(doom, pixel, plane, sidedef, tex_dex);
		pixel.y++;
	}
}

void				draw_onesided_sidedef(t_doom *doom, t_plane plane, 
							t_sidedef sidedef, int x)
{
	t_point	pixel;
	int		tex_dex = 1;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	while (pixel.y <= plane.sidedef_bottom)
	{
		find_texture_index(doom, pixel, plane, sidedef, tex_dex);
		pixel.y++;
	}
}
