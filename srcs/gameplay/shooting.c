# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

int		check_hit(t_doom *doom, t_ray ray, int sector, int prev_sector)
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
		check_hit(doom, ray, SIDEDEFS[safe_x].opp_sector, sector);
	return (/*sprite integer*/0);
}


void    shoot(t_doom *doom, int x, int y)
{
    t_ray   ray;
    int     object;

	printf("x: %d, y: %d\n", x, y);
    // ray = init_ray(doom, x);
    // object = check_hit(doom, ray, doom->i_sector, doom->i_sector);
}

void	handle_shooting(t_doom *doom)
{
	if (!handle_mouse_state(doom))
		return ;
	shoot(doom, MOUSE_X, MOUSE_Y);
}

void	shooting(t_doom *doom)
{
	if (doom->own_event.shoot == TRUE)
	{
		if (MOUSE_PRESSED)
			handle_shooting(doom);
		else
			doom->own_event.mouse_state_switched = false;
	}
}