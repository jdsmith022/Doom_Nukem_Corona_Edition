/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/27 13:43:59 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

// static int		rounder(double dbl)
// {
// 	int rounded;

// 	rounded = (int)(dbl + 0.5);
// 	return (rounded);
// }

t_sidedef		set_properties_sidedef(t_point intersect, double distance,\
	t_sidedef curr_sidedef)
{
	t_sidedef sidedef;
	
	// if (curr_sidedef.sidedef_delta.y > intersect.x)
	// 	sidedef.offset_x = rounder(intersect.y) % doom->texture_width;
	// else
	// 	sidedef.offset_x = rounder(intersect.x) % doom->texture_width;
	sidedef.offset_x = intersect.x;
	sidedef.offset_y = intersect.y;
	sidedef.distance = distance;
	sidedef.sector = curr_sidedef.sector;
	sidedef.opp_sector = curr_sidedef.opp_sector;
	sidedef.id = curr_sidedef.id;
	return (sidedef);
}

double		sidedef_intersection_distance(t_ray ray, \
	t_sidedef sidedef, t_point *intersect)
{
	double			distance;
	t_point			ray_delta;
	// t_point			sidedef_delta;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef.sidedef_delta = line_delta(sidedef.line.start, sidedef.line.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
	sidedef.line.start, sidedef.sidedef_delta);
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

	x = doom->sector[sector].i_sidedefs;
	min_distance = INFINITY;
	while (x < doom->sector[sector].n_sidedefs + doom->sector[sector].i_sidedefs)
	{
		distance = sidedef_intersection_distance(ray,\
			doom->sidedef[x], &intersect);
		if (distance < min_distance &&\
			doom->sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->sidedef[x]);
		}
		x++;
	}
	if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
		sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
	project_on_plane(doom, near_sidedef, ray.plane_x, intersect);
}
