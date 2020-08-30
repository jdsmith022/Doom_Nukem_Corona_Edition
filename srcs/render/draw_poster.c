/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poster.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 22:02:58 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/30 16:44:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

int				set_poster(t_doom *doom, int x, double distance,
					t_point intersect)
{
	t_sidedef *poster;

	poster = &doom->lib.sidedef[x];
	poster->distance = distance;
	poster->intersect = intersect;
	doom->i_sidedef = x;
	return (x);
}

static void		relocate_poster(t_doom *doom, t_sidedef *poster)
{
	poster->intersect.x -= (int)poster->line.start.x % 16;
	poster->intersect.y -= (int)poster->line.start.y % 16;
	poster->intersect.x = (int)poster->intersect.x % 16;
	poster->intersect.y = (int)poster->intersect.y % 16;
	set_offset(poster, *poster, poster->intersect, doom);
}

void			draw_poster(t_doom *doom, t_plane plane,
					int poster_index, int x)
{
	t_sector	sector;
	double		poster_height;
	t_sidedef	poster;

	poster = doom->lib.sidedef[poster_index];
	sector = doom->lib.sector[poster.sector];
	relocate_poster(doom, &poster);
	poster.distance *= cos(doom->ray_adjacent * x - (60 * (PI / 180)) / 2);
	sector.height_floor = PLAYER_HEIGHT - 10;
	sector.height_ceiling = -PLAYER_HEIGHT + 10;
	doom->texture_height = 16;
	doom->texture_width = 16;
	printf("x: %d\n", plane.x);
	set_properties_plane_sidedef(doom, poster, sector, &plane);
	draw_onesided_sidedef(doom, plane, poster, x);
	doom->texture_height = 96;
	doom->texture_width = 96;
}
