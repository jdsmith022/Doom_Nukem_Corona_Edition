
#include "../../includes/doom.h"

static void		calculate_ceiling_dist(t_doom *doom, int x, int y,
					t_sector sector)
{
	double dist;
	double diff;

	diff = doom->texture_height - doom->player_height;
	dist = (diff + sector.height_ceiling) / ((HEIGHT / 2) -\
		(y + doom->own_event.y_pitch));
	dist *= doom->dist_to_plane;
	dist /= cos(doom->ray_adjacent * x - (60 * (PI / 180)) / 2);
	doom->horizontal_plane_dist = dist;
}

static void		find_ceiling_limit(t_doom *doom, t_sector sector, int *limit)
{
	if (doom->lib.sector[doom->prev_sector].action == 1 \
	&& doom->lib.sector[doom->i_sector].action == 1)
		*limit = doom->lib.portal_ceiling;
	else
		*limit = 0;
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
		add_light_to_pixel(doom, sector, x, y);
		if (sector.slope_floor_id != -1)
			put_pixel_slope(doom, index, x, y);
		else
			row_calculations(doom, doom->horizontal_plane_dist, index,\
				doom->lib.tex_lib[tex_dex]);
		y--;
	}
}
