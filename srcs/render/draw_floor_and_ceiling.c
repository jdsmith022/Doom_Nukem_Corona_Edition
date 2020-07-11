/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor_and_ceiling.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 14:00:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/11 10:49:31 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
	height = (HEIGHT / 2) + doom->player_height;
	bpp = doom->surface->format->BytesPerPixel;
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
					t_sector sector, int y, t_sidedef sidedef)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint32	tex_dex;
	Uint8	bpp;
	double	height_floor;

	tex_dex = sector.txt_floor;
	height = (HEIGHT / 2) + doom->player_height;
	//if (sector.slope_id != -1)
	//	height -= (sector.height_floor + sector.slope_height_floor + sector.slope_height_floor);
	bpp = doom->surface->format->BytesPerPixel;
	height_floor = sector.height_floor;
	while (y < HEIGHT)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		if (sector.slope_id != -1)
			height_floor = set_properties_slope(doom, sidedef, sector);
		dist = (doom->player_std_height - height_floor)\
			/ (y - height) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		dist = fabs(dist);
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}
