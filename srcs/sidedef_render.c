/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 21:39:32 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_sidedef		set_sidedef_properties(t_point intersect, double distance,\
	t_sidedef curr_sidedef)
{
	t_sidedef sidedef;
	
	sidedef.offset_x = intersect.x;
	sidedef.offset_y = intersect.y;
	sidedef.distance = distance;
	sidedef.sector = curr_sidedef.sector;
	sidedef.opp_sector = curr_sidedef.opp_sector;
	return (sidedef);
}

double		sidedef_intersection_distance(t_ray ray, \
	t_sidedef sidef, t_point *intersect)
{
	double			distance;
	t_point			ray_delta;
	t_point			sidedef_delta;


	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef_delta = line_delta(sidef.start, sidef.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
	sidef.start, sidedef_delta);
	distance = point_distance(*intersect, ray.line.start, ray.angle);
	return (distance);
}

void		sidedef_render(t_doom *doom, t_ray ray, int prev_sector)
{
	t_point			intersect;
	t_sidedef		near_sidedef;
	double			distance;
	double			min_distance;
	int				x;

	x = 0;
	min_distance = INFINITY;
	while (x < 6) //sidedefs in sector//
	{
		distance = sidedef_intersection_distance(ray,\
			doom->sidedef[x], &intersect);
		if (distance < min_distance)
		{
			min_distance = distance;
			near_sidedef = set_sidedef_properties(intersect,\
				distance, doom->sidedef[x]);
		}
		x++;
	}
	if (near_sidedef.opp_sector != 0 && near_sidedef.opp_sector != prev_sector)
	{
		prev_sector = near_sidedef.sector;
		sidedef_render(doom, ray, near_sidedef.opp_sector);
	}
	draw_sidedef(doom, near_sidedef, ray.plane_x);
}
