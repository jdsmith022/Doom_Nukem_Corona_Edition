/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/08 12:20:52 by Malou         ########   odam.nl         */
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
	t_sidedef sidedef, t_point *intersect)
{
	double			distance;
	t_point			ray_delta;
	t_point			sidedef_delta;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef_delta = line_delta(sidedef.start, sidedef.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
	sidedef.start, sidedef_delta);
	distance = point_distance(*intersect, ray.line.start, ray.angle);
	return (distance);
}

void		sidedef_render(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	t_point			intersect;
	t_sidedef		near_sidedef;
	double			distance;
	double			min_distance;
	int				x;

	x = 0;
	min_distance = INFINITY;
	while (x < doom->sector[sector].n_sidedefs) //sidedefs in sector//
	{
		distance = sidedef_intersection_distance(ray,\
			doom->sector[sector].sidedef[x], &intersect);
		if (distance < min_distance && doom->sector[sector].sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_sidedef_properties(intersect,\
				distance, doom->sector[sector].sidedef[x]);
		}
		x++;
	}
	if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
		sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
	project_on_plane(doom, near_sidedef, ray.plane_x);
}
