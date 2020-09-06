/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_poster.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 22:02:58 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 20:07:31 by nde-wild      ########   odam.nl         */
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
	if (poster->action == 8)
		doom->cast.poster = refill_station;
	else
		doom->cast.poster = light_click;
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
	t_sidedef	*poster;
	int			safe_light_dist;

	poster = &doom->lib.sidedef[poster_index];
	calculate_ceiling_dist(doom, x, plane.sidedef_top,  doom->lib.sector[poster->sector]);
	safe_light_dist = doom->cast.horizontal_plane_dist;
	// printf("%f\n", doom->cast.horizontal_plane_dist);
	sector = doom->lib.sector[poster->sector];
	relocate_poster(doom, poster);
	poster->distance *= \
		cos(doom->cast.ray_adjacent * x - (60 * (PI / 180)) / 2);
	sector.height_floor = PLAYER_HEIGHT - 10;
	sector.height_ceiling = -PLAYER_HEIGHT + 10;
	doom->cast.texture_height = 16;
	doom->cast.texture_width = 16;
	doom->i_sidedef = poster->id;
	set_properties_plane_sidedef(doom, *poster, sector, &plane);
	doom->cast.horizontal_plane_dist = safe_light_dist;
	draw_onesided_sidedef(doom, plane, *poster, x);
	doom->cast.texture_height = 96;
	doom->cast.texture_width = 96;
}
