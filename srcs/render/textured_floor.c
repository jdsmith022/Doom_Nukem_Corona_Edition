/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textured_floor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 12:38:22 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/03 13:49:08 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	put_row(t_doom *doom, size_t index, size_t pixel_dex)
{
    size_t row_dex = 0;
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

static void	row_calculations(t_doom *doom, double dist, size_t addr_dex)
{
	t_point	texture;
	t_point	floor;
	size_t	texture_dex;
	Uint8	bpp;

	bpp = doom->lib.tex_lib[0]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % doom->texture_width;
	texture.y = (int)floor.y % doom->texture_height;
	texture_dex = ((texture.y * doom->lib.tex_lib[0]->pitch) + (texture.x * bpp));
	put_row(doom, addr_dex, texture_dex);
}

void	draw_texture_ceiling(t_doom *doom, int x, int y)
{
	double	dist;
	size_t	addr_dex;
	int		height;
	Uint8	bpp;

	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	while (y >= 0)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = (double)doom->player_std_height / (height - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y--;
	}
}

void	draw_texture_floor(t_doom *doom, int x, int y)
{
	double	dist;
	size_t	addr_dex;
	Uint8	bpp;
	int		height;

	height = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT) //need to draw to sector or height (a lot of pixel overwritting happening)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (y - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y++;
	}
}