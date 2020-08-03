#include "../../includes/doom.h"

static void		put_infection(t_doom *doom, t_sidedef infection, int x)
{
	t_plane		plane;

	// infection.action = 4;
	doom->texture_height = 16;
	doom->texture_width = 16;
	set_properties_plane(doom, infection, &plane, x);
	draw_onesided_sidedef(doom, plane, infection, x);
	doom->texture_height = 96;
	doom->texture_width = 96;
}

void		find_infection(t_doom *doom, t_ray ray, double min_distance)
{
	t_point		intersect;
	t_sidedef	near_sidedef;
	double		distance;
	double		safe;
	int			x;

	x = 0;
	safe = INFINITY;
	while (x < doom->lib.cur_len_infection)
	{
		distance = sidedef_intersection_distance(ray,\
			doom->lib.infection[x].line, &intersect);
		if (distance <= min_distance + 0.01)
		{
			min_distance = distance;
			safe = min_distance;
			near_sidedef = set_properties_sidedef(intersect,\
				distance, doom->lib.infection[x], doom);
		}
		x++;
	}
	if (safe != INFINITY)
	{
		doom->distance = min_distance;
		relocate_poster(doom, &near_sidedef);
		put_infection(doom, near_sidedef, ray.plane_x);
	}
}
