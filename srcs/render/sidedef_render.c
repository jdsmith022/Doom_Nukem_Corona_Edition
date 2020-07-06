/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/06 17:42:52 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static int			rounded(double dbl)
{
	int rounded;

	rounded = (int)(dbl + 0.5);
	return (rounded);
}

static void			set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
						t_point intersect, t_doom *doom)
{
	t_point start;
	t_point end;

	start = curr_sidedef.line.start;
	end = curr_sidedef.line.end;
	if (start.x == end.x || (start.x > end.x && start.y < end.y))
	{
		sidedef->offset = rounded(intersect.y) % doom->wall_height_std;
		sidedef->dir = 0;
	}
	else if (start.y == end.y || (start.x < end.x && start.y > end.y))
	{
		sidedef->offset = rounded(intersect.x) % doom->wall_height_std;
		sidedef->dir = 1;
	}
}

static t_sidedef	set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom)
{
	t_sidedef	sidedef;

	set_offset(&sidedef, curr_sidedef, intersect, doom);
	sidedef.distance = distance;
	sidedef.sector = curr_sidedef.sector;
	sidedef.opp_sector = curr_sidedef.opp_sector;
	sidedef.id = curr_sidedef.id;
	sidedef.txt_1 = curr_sidedef.txt_1;
	sidedef.txt_2 = curr_sidedef.txt_2;
	sidedef.txt_3 = curr_sidedef.txt_3;
	return (sidedef);
}

static double		sidedef_intersection_distance(t_ray ray,
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

void				sidedef_render(t_doom *doom, t_ray ray, int sector,
						int prev_sector)
{
	t_point		intersect;
	t_sidedef	near_sidedef;
	double		distance;
	double		min_distance;
	int			x;

	x = doom->lib.sector[sector].i_sidedefs;
	min_distance = INFINITY;
	while (x < doom->lib.sector[sector].n_sidedefs +\
		doom->lib.sector[sector].i_sidedefs)
	{
		distance = sidedef_intersection_distance(ray,\
			doom->lib.sidedef[x], &intersect);
		if (distance < min_distance &&\
			doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->lib.sidedef[x], doom);
		}
		x++;
	}
	if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
		sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
	project_on_plane(doom, near_sidedef, ray.plane_x, intersect);
}
