#include "../../includes/doom.h"

void		set_ceiling_limit(t_doom *doom, t_plane *plane, t_sidedef sidedef,
			t_sector *sector)
{
	double		height_ceiling;
	double		plane_height_std;
	int			new_height;
	int			plane_top;

	if (doom->i_sector == sector->id)
		sector->ceiling_end = 0;
	else
	{
		new_height = (HEIGHT / 2) + doom->player_height;
		plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
			* doom->dist_to_plane;
		plane_height_std = plane_height_std / 2;
		height_ceiling = (sector->height_ceiling) / \
			sidedef.prev_sidedef.distance * doom->dist_to_plane;
		plane_top = (new_height - plane_height_std) - \
			doom->own_event.y_pitch - height_ceiling - 1;
		if (plane_top < 0)
			plane_top = 0;
		sector->ceiling_end = plane_top;
	}
}
