
#include "../../includes/doom.h"

void		set_ceiling_limit(t_doom *doom, t_sidedef sidedef,
				t_sector *sector)
{
	double		height_ceiling;
	double		plane_height_std;
	int			plane_top;
	int			diff;
	double		scale;

	if (doom->i_sector == sector->id)
		sector->ceiling_end = 0;
	else
	{
		plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
			* doom->dist_to_plane;
		scale = plane_height_std / doom->texture_height;
		diff = doom->texture_height - doom->player_height;
		height_ceiling = sector->height_ceiling / \
			sidedef.prev_sidedef.distance * doom->dist_to_plane;
		plane_top = ((HEIGHT / 2) - (diff * scale)) - \
			(doom->own_event.y_pitch + height_ceiling);
		if (plane_top < 0)
			plane_top = 0;
		else if (plane_top > HEIGHT)
			plane_top = HEIGHT;
		sector->ceiling_end = plane_top;
	}
}
