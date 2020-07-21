/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/21 13:12:32 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		wall_offset(t_plane *plane, int sidedef_top)
{
	plane->wall_offset = 0;
	if (sidedef_top < 0)
	{
		plane->wall_offset = abs(sidedef_top);
		plane->sidedef_top = 0;
	}
	else
		plane->sidedef_top = sidedef_top;
}

static void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	double		height_opp_sector;
	double		height_floor;
	int			mid_top;
	int			mid_bottom;
	int			div_height_std;
	double		player_heigth;

	player_heigth = (HEIGHT / 2) + doom->player_height;
	div_height_std = plane->height_standard / 2;
	height_opp_sector = sector->height_ceiling / sidedef.distance * \
		doom->dist_to_plane;
	height_floor = sector->height_floor;
	if (sector->slope_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		height_floor += sector->slope.height_floor;
	}
	height_floor = height_floor / sidedef.distance * doom->dist_to_plane;
	mid_top = (player_heigth - div_height_std) +\
		height_opp_sector - doom->own_event.y_pitch;
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	mid_bottom = (player_heigth + div_height_std) - height_floor\
		- doom->own_event.y_pitch;
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ?\
		mid_bottom : (HEIGHT));
}

static void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	double		player_height;

	player_height = (HEIGHT / 2) + doom->player_height;
	plane->height_standard = doom->wall_height_std / sidedef.distance\
		* doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	height_floor = sector->height_floor;
	if (sector->slope_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		height_floor += sector->slope.height_floor;
	}
	height_floor = height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (player_height - div_height_std) - doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (player_height + div_height_std) -\
		doom->own_event.y_pitch - height_floor;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

void			project_on_plane(t_doom *doom, t_sidedef sidedef,
				int x, t_point intersect)
{
	t_plane		plane;
	t_sector	sector;
	t_sector	opp_sector;

	plane.intersect = intersect;
	plane.sidedef_id = sidedef.id;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sector = doom->lib.sector[sidedef.sector];
	set_properties_plane_sidedef(doom, sidedef, &sector, &plane);
	if (sidedef.opp_sector != -1)
	{
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			&opp_sector, &plane);
	}
	draw_ceiling(doom, x, sector, plane.sidedef_top);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	draw_floor(doom, x, sector, plane.sidedef_bottom);
}
