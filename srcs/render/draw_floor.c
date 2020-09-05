/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:01:34 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/05 18:07:32 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void		calculate_floor_dist(t_doom *doom, int x, int y,
					t_sector *sector)
{
	double dist;
	// double diff;

	// diff = doom->player.height - PLAYER_HEIGHT;
	dist = (doom->player.height - sector->height_floor) / \
		((y + doom->own_event.y_pitch) - (HEIGHT / 2));
	dist *= doom->cast.dist_to_plane;
	dist /= cos(doom->cast.ray_adjacent * x - (60 * (PI / 180)) / 2);
	doom->cast.horizontal_plane_dist = dist;
}

static void		find_floor_limit(t_doom *doom, t_sector sector, int *limit)
{
	if (sector.slope_floor_id != -1)
		*limit = HEIGHT;
	else
		*limit = sector.floor_end;
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int		limit;

	tex_dex = sector.txt_floor;
	bpp = doom->surface->format->BytesPerPixel;
	find_floor_limit(doom, sector, &limit);
	while (y < limit)
	{
		calculate_floor_dist(doom, x, y, &sector);
		add_light_to_pixel(doom, sector, x, y);
		index = (y * doom->surface->pitch) + (x * bpp);
		if (sector.slope_floor_id != -1)
			put_pixel_slope(doom, x, y);
		else
			row_calculations(doom, doom->cast.horizontal_plane_dist,\
				index, doom->lib.tex_lib[tex_dex]);
		y++;
	}
}
