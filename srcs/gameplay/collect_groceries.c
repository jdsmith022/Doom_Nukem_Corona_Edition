# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

int		find_shelf(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	t_point		isect;
	int			safe_x;
	int			x;
	double		dist;
	double		min_dist;

	x = SECTORS[sector].i_sidedefs;
	min_dist = INFINITY;
	while (x < SECTORS[sector].n_sidedefs + SECTORS[sector].i_sidedefs)
	{
		dist = sidedef_intersection_distance(ray, SIDEDEFS[x].line, &isect);
		if (dist <= min_dist && SIDEDEFS[x].opp_sector != prev_sector)
		{
			min_dist = dist;
			safe_x = x;
		}
		x++;
	}
	if (min_dist > 40)
		return false;
	if (SIDEDEFS[safe_x].opp_sector != -1 &&
		SIDEDEFS[safe_x].opp_sector != prev_sector)
		return (find_shelf(doom, ray, SIDEDEFS[safe_x].opp_sector, sector));
	return (*((int *)TEXTURES[SIDEDEFS[safe_x].txt_2]->userdata));
}
