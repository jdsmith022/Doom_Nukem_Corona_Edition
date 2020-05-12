/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/12 17:31:54 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	put_row(t_doom *doom, int x, int y, size_t index)
{
	size_t addr_dex;
	// size_t wall_dex;
	size_t row_dex = 0;
	char *pixels;
	char *textures;

	pixels = doom->surface->pixels;
	textures = doom->textures[row_dex]->pixels;
	addr_dex = (y * doom->surface->pitch) + (x * doom->surface->format->BytesPerPixel);
	// wall_dex = 4 * (64 * (int)texture.y + (int)texture.x);
	// row_dex = doom->graphics.row_dex;
	pixels[addr_dex] = textures[index];
	addr_dex++;
	index++;
	pixels[addr_dex] = textures[index];
	addr_dex++;
	index++;
	pixels[addr_dex] = textures[index];
}

void	draw_row(t_doom *doom, int x, int y, t_plane plane, t_sidedef sidedef)
{
	double	dist;
	// double	tru_dist;
	double	floor_x;
	double	floor_y;
	t_point		texture;
	size_t wall_index;

	(void)plane;
	(void)sidedef;
	dist = (double)32 / (y - (HEIGHT / 2));
	dist *= doom->dist_to_plane;
	// tru_dist = dist * (dist / cos(doom->angle));
	floor_x = dist * cos(doom->angle);
	floor_y = dist * sin(doom->angle);
	floor_x += doom->pos.x;
	floor_y += doom->pos.y;


	// floor_x = doom->pos.x + tru_dist;
	// floor_y = doom->pos.y + tru_dist;

	// printf("%f, %f\n", plane.intersect.x, plane.intersect.y);

	// dist = (double)HEIGHT / (2 * (double)y - (double)HEIGHT); // distance to y plane coordinate 
	// floor_x = x + cos(doom->angle) * tru_dist;
	// floor_y = y + sin(doom->angle) * tru_dist;

	// floor_x = dist / (dist + doom->dist_to_plane) * x + (1 - (dist / doom->dist_to_plane)) * doom->pos.x;
	// floor_y = dist / (dist + doom->dist_to_plane)  * y + (1 - (dist / doom->dist_to_plane)) * doom->pos.y;
	texture.x = (int)floor_x % 64;
	texture.y = (int)floor_y % 64;
	wall_index = ((texture.y * doom->textures[0]->pitch) + (texture.x * doom->textures[0]->format->BytesPerPixel));

	// texture.x = (int)(floor_x * 64) % 64; //coordinates of x,y of textureure
	// texture.y = (int)(floor_y * 64) % 64;
	put_row(doom, x, y, wall_index);
}
// var sourceIndex=(tileRow*this.fFloorTextureBuffer.width*bytesPerPixel)+(bytesPerPixel*tileColumn);
