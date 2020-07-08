/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor_and_ceiling.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 14:00:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/08 15:10:40 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = (Uint32)color;
}

static void		put_row(t_doom *doom, Uint32 tex_dex,
					Uint32 index, Uint64 pixel_dex)
{
	char *pixels;
	char *texture;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
}

static void		row_calculations(t_doom *doom, double dist, Uint32 index,
					Uint32 tex_dex)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % doom->lib.tex_lib[tex_dex]->h;
	texture.y = (int)floor.y % doom->lib.tex_lib[tex_dex]->w;
	pixel_dex = (((int)texture.y * doom->lib.tex_lib[tex_dex]->pitch)\
		+ ((int)texture.x * bpp));
	put_row(doom, tex_dex, index, pixel_dex);
}

void			draw_ceiling(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint32	height;
	Uint8	bpp;

	tex_dex = sector.txt_ceiling;
	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	while (y >= 0)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = (doom->player_std_height - sector.height_ceiling)\
			/ (height - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, index, tex_dex);
		y--;
	}
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint32	tex_dex;
	Uint8	bpp;
	double	height_floor;
	int		slope;

	tex_dex = sector.txt_floor;
	height = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	slope = doom->lib.sector[sector.id].slope_height_floor;
	if (sector.slope_id == -1)
		height_floor = sector.height_floor * slope;
	else
		height_floor = sector.height_floor;
		// height_floor = slope;
	while (y < HEIGHT)
	{
		//if (sector.id == 2)
		//	put_pixel(doom, x, y, 0xebd534);
		//else
		//	put_pixel(doom, x, y, 0x408f8d);
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = (doom->player_std_height - height_floor)\
			/ (y - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		dist = fabs(dist);
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}
