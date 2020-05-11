/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:43:16 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/11 14:53:10 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	put_row(t_doom *doom, int x, int y, t_point text)
{
	size_t addr_dex;
	size_t wall_dex;
	size_t row_dex = 0;
	char *pixels;
	char *textures;

	pixels = doom->surface->pixels;
	textures = doom->textures[row_dex]->pixels;
	addr_dex = 4 * (WIDTH * y + x);
	wall_dex = 4 * (64 * (int)text.y + (int)text.x);
	// row_dex = doom->graphics.row_dex;
	pixels[addr_dex] = textures[wall_dex];
	addr_dex++;
	wall_dex++;
	pixels[addr_dex] = textures[wall_dex];
	addr_dex++;
	wall_dex++;
	pixels[addr_dex] = textures[wall_dex];
}

void	draw_row(t_doom *doom, int x, int y, t_plane plane)
{
	double	dist;
	double	floor_x;
	double	floor_y;
	t_point		text;

	(void)plane;
	// dist = (double)32 / (y - HEIGHT / 2) * doom->dist_to_plane;
	// dist /= cos(doom->angle);
		dist = (double)HEIGHT / (2 * (double)y - (double)HEIGHT); // distance to y plane coordinate 

	floor_x = dist * cos(doom->angle) + doom->pos.x; //x,y in map calcuated from player position, distance(distance to intersect point) and angle (ray_angle)
	floor_y = dist * sin(doom->angle) + doom->pos.y;

	// floor_x = doom->pos.x + (plane.intersect.x * cos(doom->angle) * dist);
	// floor_y = doom->pos.y + (plane.intersect.x * sin(doom->angle) * dist);
	// floor_x = dist / doom->dist_to_plane * plane.intersect.x + (1 - (dist / doom->dist_to_plane)) * doom->pos.x;
	// floor_y = dist / doom->dist_to_plane * plane.intersect.y + (1 - (dist / doom->dist_to_plane)) * doom->pos.y;
	
	text.x = (int)(floor_x * 64) % 64; //coordinates of x,y of texture
	text.y = (int)(floor_y * 64) % 64;
	put_row(doom, x, y, text);
}

// void		draw_ceiling(t_doom *doom, int x, int sidedef_top)
// {
// 	int y;

// 	y = 0;
// 	while (y < sidedef_top)
// 	{
// 		put_pixel(doom, x, y, 0x5B2C6F);
// 		y++;
// 	}
// }

// void		draw_floor(t_doom *doom, int x, int y)
// {
// 	Uint32 	color;
	
// 	while (y < HEIGHT)
// 	{
// 		color = 0xffa500;
// 		put_pixel(doom, x, y, color);
// 		y++;	
// 	}
// }