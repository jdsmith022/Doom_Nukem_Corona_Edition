/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/13 11:38:06 by jessicasmit   ########   odam.nl         */
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

static void	row_calculations(t_doom *doom, double dist, size_t addr_dex)
{
	t_point	texture;
	t_point	floor;
	size_t	wall_index;

	floor.x = dist * cos(doom->angle);
	floor.y = dist * sin(doom->angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % 64;
	texture.y = (int)floor.y % 64;
	wall_index = ((texture.y * doom->textures[0]->pitch) + (texture.x * doom->textures[0]->format->BytesPerPixel));
	put_row(doom, addr_dex, wall_index);
}

void	draw_ceiling(t_doom *doom, t_plane plane, int x)
{
	double	dist;
	size_t	addr_dex;
	int y;

	y = plane.sidedef_top;
	while (y >= 0)
	{
		addr_dex = (y * doom->surface->pitch) + (x * doom->surface->format->BytesPerPixel);
		dist = (doom->wall_height - (double)32) / ((HEIGHT / 2) - y);
		dist *= doom->dist_to_plane;
		dist *= cos(doom->ray_adjacent / (x - FOV / 2));
		row_calculations(doom, dist, addr_dex);
		y--;
	}
}

void	draw_floor(t_doom *doom, t_plane plane, int x)
{
	double	dist;
	size_t	addr_dex;
	int			y;

	y = plane.sidedef_bottom;
	while (y < HEIGHT)
	{
		addr_dex = (y * doom->surface->pitch) + (x * doom->surface->format->BytesPerPixel);
		dist = (double)32 / (y - (HEIGHT / 2));
		dist *= doom->dist_to_plane;
		row_calculations(doom, dist, addr_dex);
		y++;
	}

}
