/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slope_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:22:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/06 15:06:42 by Malou         ########   odam.nl         */
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

t_point		get_biggest_distance(t_doom *doom, t_sector sector, t_sidedef hinge)
{
	int		i;
	int		max;
	double	dist;
	double	max_dist;
	t_point	side_point;
	t_point max_point;

	i = sector.i_sidedefs;
	max_dist = 0;
	max = i + sector.n_sidedefs;
	while (i < max)
	{
		if (i != hinge.id)
		{
			side_point = doom->lib.sidedef[i].line.start;
			if ((side_point.x != hinge.line.start.x  && side_point.y != hinge.line.start.y) \
			|| (side_point.x != hinge.line.end.x  && side_point.y != hinge.line.end.y))
				dist = fabs(point_line_distance(side_point, hinge.line));
			if (dist > max_dist)
			{
				max_dist = dist;
				max_point = side_point;
			}
			side_point = doom->lib.sidedef[i].line.end;
			if ((side_point.x != hinge.line.start.x  && side_point.y != hinge.line.start.y) \
			|| (side_point.x != hinge.line.end.x  && side_point.y != hinge.line.end.y))
				dist = fabs(point_line_distance(side_point, hinge.line));
			if (dist > max_dist)
			{
				max_dist = dist;
				max_point = side_point;
			}
		}
		i++;
	}
	return (max_point);
}

int			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_plane *plane)
{
	t_sector	sector;
	int			opp_side;
	t_point		opp_point;
	double		distance;

	sector = doom->lib.sector[sidedef.sector];
	//opp_point = get_biggest_distance(doom, sector, doom->lib.sidedef[sector.slope_id]);
	distance = 0;
	if (sidedef.id == sector.slope_id)
		return (doom->lib.sector[sidedef.sector].height_floor);
	opp_side = select_opp_sidedef(sector);
	//else if (sidedef.id == sector.slope_id)
	//	return (doom->lib.sector[sidedef.opp_sector].height_floor);
	opp_point = get_opp_point(sidedef, doom->lib.sidedef[opp_side]);
	if (sidedef.id != opp_side)
		distance = points_distance(sidedef.intersect, opp_point);
	//printf("%f\n", tan(sector.slope_floor) * distance);
	return ((int)(tan(sector.slope_floor) * distance));
}
