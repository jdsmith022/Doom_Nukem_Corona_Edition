/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/10 16:50:14 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
					t_point intersect, t_doom *doom)
{
	t_point start;
	t_point end;
	Uint8	diff;

	start = curr_sidedef.line.start;
	end = curr_sidedef.line.end;
	diff = find_slope_line_offset(start, end);
	if (start.x == end.x || diff == 1)
	{
		sidedef->offset = ft_rounder(intersect.y) % 96;
		sidedef->dir = 0;
	}
	else if (start.y == end.y || diff == 2)
	{
		sidedef->offset = ft_rounder(intersect.x) %  96;
		sidedef->dir = 1;
	}
}

static t_sidedef set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom)
{
	t_sidedef	sidedef;

	set_texture_properties(doom, doom->lib.sector[curr_sidedef.sector],\
		curr_sidedef.txt_1, 0);
	set_offset(&sidedef, curr_sidedef, intersect, doom);
	sidedef.distance = distance;
	sidedef.sector = curr_sidedef.sector;
	sidedef.opp_sector = curr_sidedef.opp_sector;
	sidedef.id = curr_sidedef.id;
	sidedef.txt_1 = curr_sidedef.txt_1;
	sidedef.txt_2 = curr_sidedef.txt_2;
	sidedef.txt_3 = curr_sidedef.txt_3;
	sidedef.intersect = intersect;
	return (sidedef);
}

double			sidedef_intersection_distance(t_ray ray,
					t_line line, t_point *intersect)
{
	double		distance;
	t_point		ray_delta;
	t_point		sidedef_delta;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef_delta = line_delta(line.start, line.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
		line.start, sidedef_delta);
	distance = point_distance(*intersect, ray.line.start, ray.angle);
	return (distance);
}

static int		find_intersect(t_doom *doom, t_ray ray, int sector,
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
			doom->lib.sidedef[x].line, &intersect);
		if (distance < min_distance &&\
			doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->lib.sidedef[x], doom);
		}
		x++;
	}
	// printf("render: %f, %f\n", ray.line.end.x, ray.line.end.y);
	// doom->stripe_distance[(int)ray.plane_x] = min_distance;
	// sprite_check(doom, ray, sector);
	if (min_distance != INFINITY)
	{
		if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
			sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
		return (project_on_plane(doom, near_sidedef, ray.plane_x));
	}
	return (0);
}

int				sidedef_render(t_doom *doom, t_ray ray, int sector,
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
			doom->lib.sidedef[x].line, &intersect);
		if (distance < min_distance &&\
			doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			min_distance = distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->lib.sidedef[x], doom);
		}
		x++;
	}
	if (min_distance != INFINITY)
	{
		if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
			sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
		return (project_on_plane(doom, near_sidedef, ray.plane_x));
	}
	return (0);
}
