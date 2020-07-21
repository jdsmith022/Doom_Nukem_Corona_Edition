# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

t_ray init_ray(t_doom *doom, int x)
{
	t_ray	ray;

	ray.angle = clamp_angle(doom->dir_angle - (FOV / 2) +  doom->ray_adjacent * x);
	ray.line.start = doom->pos;
	ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
	ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
	ray.plane_x = x;
	return (ray);
}

int		find_shelf(t_doom *doom, t_ray ray, int sector,
						int prev_sector)
{
	t_point		intersect;
	int			safe_x;
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
				safe_x = x;
		}
		x++;
	}
	if (min_distance != INFINITY)
	{
		if (doom->lib.sidedef[safe_x].opp_sector != -1 && doom->lib.sidedef[safe_x].opp_sector != prev_sector)
			return (find_shelf(doom, ray, doom->lib.sidedef[safe_x].opp_sector, sector));
		return (doom->lib.tex_lib[doom->lib.sidedef[safe_x].txt_2]->userdata);
	}
	return (0);
}