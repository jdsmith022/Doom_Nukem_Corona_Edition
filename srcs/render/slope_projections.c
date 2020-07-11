/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slope_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:22:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/11 10:49:13 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_sidedef	get_other_side(t_doom *doom, t_sidedef sidedef, t_sector sector)
{
	t_point		start;
	t_point		end;
	t_point		opp_start;
	t_point		opp_end;
	size_t		i;

	start = sidedef.line.start;
	end = sidedef.line.end;
	i = sector.i_sidedefs;
	while (i < sector.i_sidedefs + sector.n_sidedefs)
	{
		opp_start = doom->lib.sidedef[i].line.start;
		opp_end = doom->lib.sidedef[i].line.end;
		if (((start.x == opp_start.x && start.y == opp_start.y) &&\
			(end.x == opp_end.x && end.y == opp_end.y)) ||\
			((start.x == opp_end.x && start.y == opp_end.y) &&\
			(end.x == opp_start.x && end.y == opp_start.y)))
		{
			doom->lib.sidedef[i].intersect = sidedef.intersect;
			return (doom->lib.sidedef[i]);
		}
		i++;
	}
	return (doom->lib.sidedef[i]);
}

t_point		get_connecting_point(t_sidedef sidedef, t_sidedef opp_sidedef)
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

int			get_opp_sidedef(t_sector sector)
{
	int			first_sidedef;

	first_sidedef = sector.i_sidedefs;
	if (sector.slope_id == first_sidedef ||\
		sector.slope_id == first_sidedef + 1)
		return (sector.slope_id + 2);
	return (sector.slope_id - 2);
}

// t_point		get_biggest_distance(t_doom *doom, t_sector sector, t_sidedef hinge)
// {
// 	int		i;
// 	int		max;
// 	double	dist;
// 	double	max_dist;
// 	t_point	side_point;
// 	t_point max_point;

// 	i = sector.i_sidedefs;
// 	max_dist = 0;
// 	max = i + sector.n_sidedefs;
// 	while (i < max)
// 	{
// 		if (i != hinge.id)
// 		{
// 			side_point = doom->lib.sidedef[i].line.start;
// 			if ((side_point.x != hinge.line.start.x  && side_point.y != hinge.line.start.y) \
// 			|| (side_point.x != hinge.line.end.x  && side_point.y != hinge.line.end.y))
// 			{
// 				dist = fabs(point_line_distance(side_point, hinge.line));
// 				if (dist > max_dist)
// 				{
// 					max_dist = dist;
// 					max_point = side_point;
// 				}
// 			}
// 			side_point = doom->lib.sidedef[i].line.end;
// 			if ((side_point.x != hinge.line.start.x  && side_point.y != hinge.line.start.y) \
// 			|| (side_point.x != hinge.line.end.x  && side_point.y != hinge.line.end.y))
// 			{
// 				dist = fabs(point_line_distance(side_point, hinge.line));
// 				if (dist > max_dist)
// 				{
// 					max_dist = dist;
// 					max_point = side_point;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	return (max_point);
// }

int			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_plane *plane)
{
	t_sector	sector;
	int			opp_side;
	t_point		opp_point;
	double		distance;
	double		height;

	distance = 0;
	if (sidedef.sector != sector.id)
		sidedef = get_other_side(doom, sidedef, sector);
	if (sidedef.id == sector.slope_id)
		return (doom->lib.sector[sidedef.sector].height_floor);
	opp_side = get_opp_sidedef(sector);
	conn_side = get_connecting_point(sidedef,\
		doom->lib.sidedef[sector.slope_id]);
	if (sidedef.id != sector.slope_id && sidedef.id != opp_side)
		distance = points_distance(sidedef.intersect, conn_side);
	if (sidedef.id == opp_side)
		distance = fabs(point_line_distance(sidedef.line.end,\
			doom->lib.sidedef[sector.slope_id].line));
	doom->lib.sector[sector.id].slope_height_floor = tan(sector.slope_floor) * distance;
	height = sector.height_floor + doom->lib.sector[sector.id].slope_height_floor;
	return (height);
}
