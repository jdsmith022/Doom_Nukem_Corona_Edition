/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor_ceiling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/03 12:37:45 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	put_row(t_doom *doom, size_t addr_dex, size_t texture_dex)
{
	size_t row_dex = 0; //wont' be needed
	char *pixels;
	char *textures;

	pixels = doom->surface->pixels;
	textures = doom->textures[row_dex]->pixels;
	pixels[addr_dex] = textures[texture_dex];
	addr_dex++;
	texture_dex++;
	pixels[addr_dex] = textures[texture_dex];
	addr_dex++;
	texture_dex++;
	pixels[addr_dex] = textures[texture_dex];
}

static void	row_calculations(t_doom *doom, double dist, size_t addr_dex)
{
	t_point	texture;
	t_point	floor;
	size_t	texture_dex;
	Uint8	bpp;

	bpp = doom->textures[0]->format->BytesPerPixel;
	floor.x = dist * cos(doom->angle);
	floor.y = dist * sin(doom->angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % doom->texture_width;
	texture.y = (int)floor.y % doom->texture_height;	
	texture_dex = ((texture.y * doom->textures[0]->pitch) + (texture.x * bpp));
	put_row(doom, addr_dex, texture_dex);
}

void	draw_ceiling(t_doom *doom, int x, int y)
{
	double	dist;
	size_t	addr_dex;
	Uint8	bpp;
	int		height;

	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	(void)doom;
	while (y >= 0)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_height / (height - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y--;
	}
}

void	draw_floor(t_doom *doom, int x, t_plane plane, t_sector sector)
{
	double	dist;
	size_t	addr_dex;
	Uint8	bpp;
	int 	y;
	int		height;
	
	(void)sector;
	y = plane.floor_start;
	height = (HEIGHT - doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT) //need to draw to sector size not bottom of screen (a lot of pixel overwritting happening)
	{
		addr_dex = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_height / (y - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, addr_dex);
		y++;
	}
}
