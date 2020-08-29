#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/render.h"


int				find_shelf(t_lib lib, t_ray ray, int sector, int prev_sector)
{
	t_point		isect;
	int			safe_x;
	int			x;
	double		dist;
	double		min_dist;

	x = lib.sector[sector].i_sidedefs;
	min_dist = INFINITY;
	while (x < lib.sector[sector].n_sidedefs + lib.sector[sector].i_sidedefs)
	{
		dist = sidedef_intersection_distance(ray, lib.sidedef[x].line, &isect);
		if (dist <= min_dist && lib.sidedef[x].opp_sector != prev_sector)
		{
			min_dist = dist;
			safe_x = x;
		}
		x++;
	}
	if (min_dist > 40)
		return (false);
	if (lib.sidedef[safe_x].opp_sector != -1 &&
		lib.sidedef[safe_x].opp_sector != prev_sector)
		return (find_shelf(lib, ray, lib.sidedef[safe_x].opp_sector, sector));
	return (*((int *)lib.tex_lib[lib.sidedef[safe_x].txt_2]->userdata));
}
