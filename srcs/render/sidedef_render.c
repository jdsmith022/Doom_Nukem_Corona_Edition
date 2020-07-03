/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/16 18:03:28 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_sidedef	set_properties_sidedef(t_point intersect, double distance,\
	t_sidedef curr_sidedef)
{
	t_sidedef	sidedef;

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
	double		distance;
	t_point		ray_delta;
	t_point		sidedef_delta;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef_delta = line_delta(sidedef.line.start, sidedef.line.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
	sidedef.line.start, sidedef_delta);
	distance = point_distance(*intersect, ray.line.start, ray.angle);
	return (distance);
}

void		sidedef_render(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	t_point		intersect;
	t_sidedef	near_sidedef;
	double		distance;
	double		min_distance;
	int			x;

	// printf("start\n");
	x = doom->lib.sector[sector].i_sidedefs;
	min_distance = INFINITY;
	while (x < doom->lib.sector[sector].n_sidedefs +\
		doom->lib.sector[sector].i_sidedefs)
	{
				// if (sector == 1)
		distance = sidedef_intersection_distance(ray,\
			doom->lib.sidedef[x], &intersect);
		// printf("%i %f %f %f %f\n", x, doom->lib.sidedef[x].line.start.x, doom->lib.sidedef[x].line.start.y, doom->lib.sidedef[x].line.end.x, doom->lib.sidedef[x].line.end.y);
		// printf("%i %f %i %i\n", x, distance, doom->lib.sidedef[x].opp_sector, prev_sector);
		if (distance < min_distance &&\
			doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->lib.sidedef[x]);
		}
		x++;
	}
	// printf("%d -- %d -- %d -- %d\n", sector, near_sidedef.opp_sector, doom->lib.sector[sector].i_sidedefs, prev_sector);
	// printf("esc %i %i\n", x, near_sidedef.opp_sector);
	if (min_distance != INFINITY)
	{
		if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
		{
			// printf("bf %i %i\n", near_sidedef.opp_sector, near_sidedef.opp_sidedef);
			sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
			// printf("af %i %i\n", near_sidedef.opp_sector, near_sidedef.opp_sidedef);
		}
		// printf("%d -- %d -- %d -- %d\n", sector, near_sidedef.opp_sector, doom->lib.sector[sector].i_sidedefs, prev_sector);
		project_on_plane(doom, near_sidedef, ray.plane_x, intersect);
	}
}
