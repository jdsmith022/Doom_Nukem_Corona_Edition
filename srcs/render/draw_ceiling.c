#include "../../includes/doom.h"

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
	limit = 0;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_ceiling;
	while (y >= limit)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = (doom->player_std_height - sector.height_ceiling)\
			/ ((HEIGHT / 2 + doom->player_height)\
			- (y + doom->own_event.y_pitch));
		dist *= doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		doom->horizontal_plane_dist = dist;
		light_floor_ceiling(doom, sector, x, y);
		row_calculations(doom, doom->horizontal_plane_dist, index, tex_dex);
		y--;
	}
}
