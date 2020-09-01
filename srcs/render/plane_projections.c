/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:36 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/01 20:44:09 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void		set_sector_properties(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	set_ceiling_limit(doom, sidedef, sector);
	set_floor_limit(doom, plane, sidedef, sector);
	if (sector->action == 1)
		doom->lib.portal_ceiling = plane->sidedef_top;
}

void			set_properties_plane(t_doom *doom, t_sidedef sidedef,
					t_plane *plane, t_sector *sector)
{
	t_sector	opp_sector;
	double		fov;

	fov = 60 * (PI / 180);
	sidedef.distance *= cos(doom->cast.ray_adjacent * plane->x - fov / 2);
	sidedef.prev_sidedef.distance *= \
		cos(doom->cast.ray_adjacent * plane->x - fov / 2);
	plane->intersect = sidedef.intersect;
	set_properties_plane_sidedef(doom, sidedef, *sector, plane);
	if (sidedef.opp_sector != -1)
	{
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			opp_sector, plane);
	}
	set_sector_properties(doom, sidedef, sector, plane);
}

static void		set_values_clipping_sprites_2(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	if (plane.mid_texture_top == HEIGHT)
		doom->lib.sector[sidedef.sector].mid_top[x] = -1;
	else
		doom->lib.sector[sidedef.sector].mid_top[x] =\
			plane.mid_texture_top;
	if (plane.mid_texture_bottom == 0)
		doom->lib.sector[sidedef.sector].mid_bottom[x] = -1;
	else
		doom->lib.sector[sidedef.sector].mid_bottom[x] = \
			plane.mid_texture_bottom;
}

void			set_values_clipping_sprites(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	if (plane.sidedef_bottom >= 0 && plane.sidedef_bottom <= HEIGHT)
		doom->lib.sector[sidedef.sector].bottom[x] = \
			plane.sidedef_bottom;
	else
		doom->lib.sector[sidedef.sector].bottom[x] = 0;
	if (plane.sidedef_top >= 0 && plane.sidedef_top <= HEIGHT)
		doom->lib.sector[sidedef.sector].top[x] = plane.sidedef_top;
	else
		doom->lib.sector[sidedef.sector].top[x] = 0;
	if (sidedef.opp_sector != -1 || sidedef.action == 6)
		set_values_clipping_sprites_2(doom, plane, sidedef, x);
	else
	{
		doom->lib.sector[sidedef.sector].mid_bottom[x] = 0;
		doom->lib.sector[sidedef.sector].mid_top[x] = 0;
	}
}

void			project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	plane.x = x;
	sector = doom->lib.sector[sidedef.sector];
	set_properties_plane(doom, sidedef, &plane, &sector);
	set_values_clipping_sprites(doom, plane, sidedef, x);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else if (sidedef.action == WINDOW)
		save_window(doom, plane, sidedef, x);
	else if (sidedef.opp_sector != -1)
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (sector.action != OUTSIDE)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	draw_floor(doom, x, sector, plane.sidedef_bottom);
	if (sidedef.poster != -1)
		draw_poster(doom, plane, sidedef.poster, x);
}
