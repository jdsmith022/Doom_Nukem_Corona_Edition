#include "../../includes/doom.h"

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	int		i;
	int		y_bottom;
	// int		y_top;
	int		mid_bottom;

	mid_bottom = 0;
	i = 0;
	while (i < sprite.n_sector)
	{
		mid_bottom =\
		doom->lib.sector[sprite.prev_sectors[i]].sidedef_mid_bottom[x];
		if (mid_bottom == -1)
			return (-1);
		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].sidedef_bottom[x];
		if (y_bottom > 0 && y_bottom < HEIGHT && y_bottom < screen_y)
			return (-1);
		if (mid_bottom > 0 && mid_bottom < HEIGHT && mid_bottom < screen_y)
			return (-1);
		i++;
	}
	return (1);
}
