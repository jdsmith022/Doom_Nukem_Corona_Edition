/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/12 18:00:16 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	put_row(t_doom *doom, size_t addr_dex, size_t index)
{
	size_t row_dex = 0; //wont' be needed
	char *pixels;
	char *textures;

	pixels = doom->surface->pixels;
	textures = doom->textures[row_dex]->pixels;
	pixels[addr_dex] = textures[index];
	addr_dex++;
	index++;
	pixels[addr_dex] = textures[index];
	addr_dex++;
	index++;
	pixels[addr_dex] = textures[index];
}

void	draw_ceiling(t_doom *doom, int x, int y)
{
	double	dist;
	t_point	floor;
	size_t	addr_dex;
	t_point	texture;
	size_t	wall_index;

	addr_dex = (y * doom->surface->pitch) + (x * doom->surface->format->BytesPerPixel);
	dist = (doom->wall_height - (double)32) / ((HEIGHT / 2) - y);
	dist *= doom->dist_to_plane;
	dist *= cos(doom->ray_adjacent / (x - FOV / 2));
	floor.x = dist * cos(doom->angle);
	floor.y = dist * sin(doom->angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % 64;
	texture.y = (int)floor.y % 64;
	wall_index = ((texture.y * doom->textures[0]->pitch) + (texture.x * doom->textures[0]->format->BytesPerPixel));
	put_row(doom, addr_dex, wall_index);
}

void	draw_floor(t_doom *doom, int x, int y)
{
	double	dist;
	t_point	floor;
	size_t	addr_dex;
	t_point	texture;
	size_t	wall_index;

	addr_dex = (y * doom->surface->pitch) + (x * doom->surface->format->BytesPerPixel);
	dist = (double)32 / (y - (HEIGHT / 2));
	dist *= doom->dist_to_plane;
	dist *= cos(doom->ray_adjacent / (x - FOV / 2));
	floor.x = dist * cos(doom->angle);
	floor.y = dist * sin(doom->angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % 64;
	texture.y = (int)floor.y % 64;
	wall_index = ((texture.y * doom->textures[0]->pitch) + (texture.x * doom->textures[0]->format->BytesPerPixel));
	put_row(doom, addr_dex, wall_index);
}
