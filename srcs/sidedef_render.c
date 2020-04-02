/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 13:37:04 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


double		intersection_distance(t_line ray, t_sidedef sidedef, double angle, t_intersect *intersect)
{
	double			distance;
	t_point			ray_delta;
	t_point			sidedef_delta;

	ray_delta = line_delta(ray.start, ray.end);
	sidedef_delta = line_delta(sidedef.start, sidedef.end);
	*intersect = line_intersection(ray.start, ray_delta,\
	sidedef.start, sidedef_delta);
	distance = point_distance(intersect->point, ray.start, angle);
	return (distance);
}

void		sidedef_render(t_doom *doom, t_line ray, double angle, int sector, int column)
{
	t_intersect		intersect;
	t_intersect		min_intersect;
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
		distance = intersection_distance(ray, doom->sidedef[x], angle , &intersect);
		if (distance < min_distance && distance > 0)
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
		sidedef_render(doom, ray, angle, min_intersect.opp_sector, column);
	}
	draw_column(doom, min_intersect, column);
}
