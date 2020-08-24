#include "../../includes/doom.h"

void	light_floor_ceiling(t_doom *doom, t_sector sector, int x, int y)
{
	double dist;

	dist = doom->horizontal_plane_dist;
	if (doom->light == TRUE)
	{
		if (sector.light == TRUE)
			doom->distance = sector.light_level;
		else
			doom->distance = 0.15;
	}
	else
	{
		doom->distance = dist;
		doom->distance = 1 / ((float)doom->distance / 70.0);
		doom->distance =\
			x > WIDTH / 2 ? doom->distance - (x - (float)WIDTH / 2.0) *\
			1.0 / (float)WIDTH : +doom->distance - ((float)WIDTH / 2.0 - x) * 1.0 / (float)WIDTH;
		doom->distance =\
			y > HEIGHT / 2 ? doom->distance - (y - (float)HEIGHT / 2.0) *\
			1.0 / (float)HEIGHT : +doom->distance - ((float)HEIGHT / 2.0 - y) * 1.0 / (float)HEIGHT;
	}
}
