#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"

t_sidedef	set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom)
{
	t_sidedef	sidedef;

	set_texture_properties(doom);
	set_offset(&sidedef, curr_sidedef, intersect, doom);
	sidedef.distance = distance;
	sidedef.distance = point_distance(intersect, doom->pos, doom->ray_angle);
	sidedef.line.start = curr_sidedef.line.start;
	sidedef.line.end = curr_sidedef.line.end;
	sidedef.sector = curr_sidedef.sector;
	sidedef.opp_sector = curr_sidedef.opp_sector;
	sidedef.id = curr_sidedef.id;
	sidedef.txt_1 = curr_sidedef.txt_1;
	sidedef.txt_2 = curr_sidedef.txt_2;
	sidedef.txt_3 = curr_sidedef.txt_3;
	sidedef.intersect = intersect;
	sidedef.line = curr_sidedef.line;
	sidedef.action = curr_sidedef.action;
	sidedef.prev_sidedef = doom->prev_sidedef;
	return (sidedef);
}

static int			is_opp_sidedef(t_doom *doom, int id, t_sidedef opp_line)
{
	t_point start;
	t_point end;
	t_point opp_start;
	t_point opp_end;
	t_line	line;

	line = doom->lib.sidedef[id].line;
	start = line.start;
	end = line.end;
	opp_start = opp_line.line.start;
	opp_end = opp_line.line.end;
	if (((start.x == opp_start.x && start.y == opp_start.y) &&\
			(end.x == opp_end.x && end.y == opp_end.y)) ||\
			((start.x == opp_end.x && start.y == opp_end.y) &&\
			(end.x == opp_start.x && end.y == opp_start.y)))
		return (0);
	return (-1);
}

double				sidedef_intersection_distance(t_ray ray,
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

void			sidedef_render(t_doom *doom, t_ray ray, int sector,
						int prev_sector)
{
	t_point		intersect;
	t_sidedef	near_sidedef;
	double		distance;
	double		min_distance;
	int			x;
	int			save_poster;

	x = doom->lib.sector[sector].i_sidedefs;
	min_distance = INFINITY;
	doom->stripe_distance[(int)ray.plane_x] = INFINITY;
	if (doom->lib.sector[sector].action == OUTSIDE)
		sidedef_render_skybox(doom, ray, doom->lib.sky_sd);
	save_poster = -1;
	while (x < doom->lib.sector[sector].n_sidedefs +\
		doom->lib.sector[sector].i_sidedefs)
	{
		distance = sidedef_intersection_distance(ray,\
			doom->lib.sidedef[x].line, &intersect);
		if (distance <= min_distance + 0.01 &&\
			((doom->lib.sidedef[x].opp_sector != prev_sector) ||\
			(doom->lib.sidedef[x].action == 5 && is_opp_sidedef(doom,\
			doom->prev_sidedef.id, doom->lib.sidedef[x]) != 0)))
		{
			if (doom->lib.sidedef[x].action == 4 || \
			doom->lib.sidedef[x].action == 8)
			{
				doom->i_sidedef = x;
				save_poster = \
					init_poster(x, distance, intersect, &doom->lib.sidedef[x]);
			}
			else
			{
				min_distance = distance;
				if (doom->lib.sidedef[x].opp_sector == -1)
					doom->stripe_distance[(int)ray.plane_x] = min_distance; //changed
				near_sidedef = set_properties_sidedef(intersect,\
					distance, doom->lib.sidedef[x], doom);
				if (doom->lib.sidedef[x].action == 2 && doom->lib.sidedef[x].distance < 100)
					relocate_moving_wall(&intersect, &near_sidedef, doom, x);
			}
			near_sidedef.poster = save_poster;
		}
		x++;
	}
	// doom->stripe_distance[(int)ray.plane_x] = min_distance;
	sprite_check(doom, ray, sector, prev_sector);
	if (min_distance != INFINITY)
	{
		if (near_sidedef.opp_sector != -1 &&\
		(near_sidedef.opp_sector != prev_sector || near_sidedef.action == 5))
		{
			doom->prev_sidedef.id = near_sidedef.id;
			doom->prev_sidedef.distance = near_sidedef.distance;
			doom->prev_sidedef.intersect = near_sidedef.intersect;
			if (near_sidedef.action == 5)
				ray.line.start = near_sidedef.intersect;
			sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
		}
		doom->distance = min_distance;
		project_on_plane(doom, near_sidedef, ray.plane_x);
	}
}
