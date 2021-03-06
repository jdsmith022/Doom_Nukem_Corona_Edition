/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_row.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:01:48 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 12:39:36 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void			put_pixel_slope(t_doom *doom, int x, int y)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
		pixels[(y * WIDTH + x)] = SLOPE_COLOR;
}

static void		put_row(t_doom *doom, SDL_Surface *lib,
					Uint32 index, Uint64 pixel_dex)
{
	char	*pixels;
	char	*texture;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	pixels = doom->surface->pixels;
	texture = lib->pixels;
	r = texture[pixel_dex];
	g = texture[pixel_dex + 1];
	b = texture[pixel_dex + 2];
	add_saturation(&r, &g, &b, doom->cast.distance);
	pixels = doom->surface->pixels;
	texture = lib->pixels;
	pixels[index] = r;
	index++;
	pixels[index] = g;
	index++;
	pixels[index] = b;
}

void			row_calculations(t_doom *doom, double dist, Uint32 index,
					SDL_Surface *lib)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = lib->format->BytesPerPixel;
	floor.x = dist * cos(doom->cast.ray_angle);
	floor.y = dist * sin(doom->cast.ray_angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % doom->cast.texture_width;
	texture.y = (int)floor.y % doom->cast.texture_height;
	if (texture.x >= 0 && texture.x < WIDTH && \
	texture.y >= 0 && texture.x < HEIGHT)
	{
		pixel_dex = (((int)texture.y * lib->pitch)\
		+ ((int)texture.x * bpp));
		put_row(doom, lib, index, pixel_dex);
	}
}
