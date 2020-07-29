#include "../../includes/doom.h"

static void	calculate_floor_dist(t_doom *doom, int x, int y, t_sector *sector)
{
	double dist;

	dist = ((doom->player_std_height - sector->height_floor)\
		/ ((y + doom->own_event.y_pitch) -\
		((HEIGHT / 2) + doom->player_height)));
	if (sector->slope_id != -1)
		sector->height_floor += sector->slope.delta_height;
	sector->height_floor = fabs(sector->height_floor);
	dist *= doom->dist_to_plane;
	dist /= cos(doom->ray_adjacent * x - FOV / 2);
	doom->horizontal_plane_dist = dist;
}

static void		find_floor_limit(t_doom *doom, t_sector sector, int *limit)
{
	if (doom->lib.sector[doom->prev_sector].outside)
		*limit = doom->lib.portal_floor;
	else if (sector.slope_id != -1)
		*limit = sector.slope.bottom_plane;
	else
		*limit = HEIGHT;
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint8	bpp;
	int		limit;

	doom->tex_dex = sector.txt_floor;
	bpp = doom->surface->format->BytesPerPixel;
	find_floor_limit(doom, sector, &limit);
	while (y < limit)
	{
		calculate_floor_dist(doom, x, y, &sector);
		light_floor_ceiling(doom, sector, x, y);
		index = (y * doom->surface->pitch) + (x * bpp);
		row_calculations(doom, doom->horizontal_plane_dist, index, doom->lib.tex_lib[doom->tex_dex]);
		y++;
	}
}
