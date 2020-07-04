/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   horizontal_texture.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 12:38:22 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/04 13:45:50 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	put_row(t_doom *doom, Uint32 index, Uint64 pixel_dex)
{
    Uint32 row_dex = 0;
	char *pixels;
	char *texture;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[row_dex]->pixels;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
}

static void	row_calculations(t_doom *doom, double dist, Uint32 addr_dex)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = doom->lib.tex_lib[0]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % doom->texture_width;
	texture.y = (int)floor.y % doom->texture_height;
	pixel_dex = (((int)texture.y * doom->lib.tex_lib[0]->pitch) + ((int)texture.x * bpp));
	// printf("index: %d\n", pixel_dex);
	put_row(doom, addr_dex, pixel_dex);
}

void	draw_texture_ceiling(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	addr_dex;
	Uint32	height;
	Uint8	bpp;

	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	while (y >= 0)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (height - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y--;
	}
}

void	draw_texture_floor(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	addr_dex;
	Uint32	height;
	Uint8	bpp;

	height = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (y - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y++;
	}
}