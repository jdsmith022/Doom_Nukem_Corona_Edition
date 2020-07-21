# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

t_ray init_ray(t_doom *doom, int x)
{
	t_ray	ray;

	ray.ange = clamp_angle(doom->dir_angle - (FOV / 2) +  doom->ray_adjacent * x));
	ray.line.start = doom->pos;
	ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
	ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
	ray.plane_x = x;
}

Uint8		find_shelf(t_doom *doom, t_ray ray, int sector,
						int prev_sector)
{
	t_point		intersect;
	Uint8		txt_action;
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
		if (distance <= min_distance &&\
			doom->lib.sidedef[x].opp_sector != prev_sector)
		{
				min_distance = distance;
				txt_action = (Uint8)doom->lib.sidedef[x].txt_2->userdata;
		}
		x++;
	}
	if (min_distance != INFINITY)
	{
		if (near_sidedef.opp_sector != -1 && near_sidedef.opp_sector != prev_sector)
			txt_action = sidedef_render(doom, ray, near_sidedef.opp_sector, sector);
		return (txt_action)
	}
	return (0);
}