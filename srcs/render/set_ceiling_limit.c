#include "../../includes/doom.h"

int		set_ceiling_limit(t_doom *doom, t_plane *plane, t_sidedef sidedef,
			t_sector *sector)
{
	double		height_ceiling;
	double		plane_height_std;
	int			div_height_std;
	int			plane_top;
	int			new_height;

	if (doom->i_sector == sector->id)
		sector->ceiling_end = 0;
	new_height = (HEIGHT / 2) + doom->player_height;
	plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
		* doom->dist_to_plane;
	div_height_std = plane_height_std / 2 + sector->height_ceiling;
	// height_ceiling = (sector->height_ceiling + sector->slope.bottom_height) /\
		sidedef.prev_sidedef.distance * doom->dist_to_plane;
	plane_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	if (plane_top <= plane->sidedef_top)
		plane_top = 0;
	sector->ceiling_end = plane_top;
}
