#include "../../includes/doom.h"

static void		calculate_ceiling_dist(t_doom *doom, int x, int y,
					t_sector sector)
{
	double dist;

	dist = (doom->player_std_height + sector.height_ceiling)\
		/ ((HEIGHT / 2 + doom->player_height)\
		- (y + doom->own_event.y_pitch));
	dist *= doom->dist_to_plane;
	dist /= cos(doom->ray_adjacent * x - FOV / 2);
	doom->horizontal_plane_dist = dist;
}

static void		find_ceiling_limit(t_doom *doom, t_sector sector, int *limit)
{
	if (doom->lib.sector[doom->prev_sector].outside \
	&& doom->lib.sector[doom->i_sector].outside)
		*limit = doom->lib.portal_ceiling;
	else
		*limit = sector.ceiling_end;
}

void			draw_ceiling(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int		limit;

	tex_dex = sector.txt_ceiling;
	bpp = doom->surface->format->BytesPerPixel;
	find_ceiling_limit(doom, sector, &limit);
	while (y > limit)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		calculate_ceiling_dist(doom, x, y, sector);
		light_floor_ceiling(doom, sector, x, y);
		row_calculations(doom, doom->horizontal_plane_dist, index,\
			doom->lib.tex_lib[tex_dex]);
		y--;
	}
}
