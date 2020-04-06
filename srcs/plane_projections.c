/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou          #+#    #+#                */
/*   Updated: 2020/04/06 14:49:32 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		set_properties_portal(t_doom *doom, t_plane *plane,\
	t_sidedef sidedef, int id)
{
	double		height_opp_sector;

	height_opp_sector = doom->sector[id].height_ceiling -\
		doom->sector[id].height_floor;
	height_opp_sector = height_opp_sector / sidedef.distance *\
		doom->dist_to_plane;
	plane->mid_texture_top = (HEIGHT / 2 - height_opp_sector / 2);
	plane->mid_textur_bottom = (HEIGHT / 2 + height_opp_sector / 2);
}

t_plane		set_plane_properties(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane 	plane;
	int			id;
	double		floor_corr;
	double		sidedef_height;

	id = sidedef.sector;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	ft_bzero(&plane, sizeof(plane));
	sidedef_height = doom->sector[id].height_ceiling -\
		doom->sector[id].height_floor;
	sidedef_height = sidedef_height / sidedef.distance *\
		 doom->dist_to_plane;
	floor_corr = doom->sector[id].height_floor - 0;
	floor_corr = floor_corr / sidedef.distance * doom->dist_to_plane;
	plane.sidedef_top =  (HEIGHT / 2 - (sidedef_height + floor_corr) / 2);
	plane.sidedef_bottom = HEIGHT / 2 + sidedef_height / 2;
	set_properties_portal(doom, &plane, sidedef, sidedef.opp_sector);
	return (plane);
}

void	project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane plane;

	plane = set_plane_properties(doom, sidedef, x);
	draw_ceiling(doom, (int)plane.sidedef_top, sidedef.sector, x);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	draw_floor(doom, sidedef.sector, x, (int)plane.sidedef_bottom);
}