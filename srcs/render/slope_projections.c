/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slope_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:22:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/27 14:11:31 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_point		get_opp_point(t_sidedef sidedef, t_sidedef opp_sidedef)
{
	t_point		start;
	t_point		end;
	t_point		opp_start;
	t_point		opp_end;

	start = sidedef.line.start;
	end = sidedef.line.end;
	opp_start = opp_sidedef.line.start;
	opp_end = opp_sidedef.line.end;
	if ((start.x == opp_start.x && start.y == opp_start.y) ||
		(start.x == opp_end.x && start.y == opp_end.y))
		return (start);
	return (end);
}

int		select_opp_sidedef(t_sector sector)
{
	int		first_sidedef;

	first_sidedef = sector.i_sidedefs;
	if (sector.slope_id == first_sidedef || sector.slope_id == first_sidedef + 1)
		return (sector.slope_id + 2);
	return (sector.slope_id - 2);
}

int			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_plane *plane)
{
	t_sector	sector;
	int			opp_side;
	t_point		opp_point;
	double		distance;

	sector = doom->lib.sector[sidedef.sector];
	opp_side = select_opp_sidedef(sector);
	if (sidedef.id == opp_side)
		return (plane->sidedef_bottom);
	else if (sidedef.id == sector.slope_id)
		return (doom->lib.sector[sidedef.opp_sector].height_floor);
	opp_point = get_opp_point(sidedef, doom->lib.sidedef[opp_side]);
	distance = points_distance(plane->intersect, opp_point);
	return ((int)(tan(sector.slope_floor) * distance));
}
