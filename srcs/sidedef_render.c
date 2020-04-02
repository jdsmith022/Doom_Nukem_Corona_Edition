/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 15:52:31 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		sidedef_render(t_doom *doom, t_line ray, int sector, int column)
{
	t_intersect		intersect;
	t_intersect		min_intersect;
	t_line			side;
	double			distance;
	double			min_distance;
	int				prev_sector;
	int				x;

	x = 0;
	sector = 1;
	prev_sector = 1;
	min_distance = INFINITY;
	while (x < 5) //sidedefs in sector//
	{
		side.start = doom->sidedef[x].start;
		side.end = doom->sidedef[x].end;
		distance = line_intersection_distance(ray, side, ray.angle , &intersect);
		if (distance < min_distance)
		{
			min_distance = distance;
			min_intersect.point.x = intersect.point.x;
			min_intersect.point.y = intersect.point.y;
			min_intersect.obj_dist = distance;
			min_intersect.sector = doom->sidedef[x].sector;
			min_intersect.opp_sector = doom->sidedef[x].opp_sector;
		}
		x++;
	}
	if (min_intersect.opp_sector != -1 && min_intersect.sector != prev_sector)
	{
		prev_sector = min_intersect.sector;
		sidedef_render(doom, ray, min_intersect.opp_sector, column);
	}
	draw_column(doom, min_intersect, column);
}
