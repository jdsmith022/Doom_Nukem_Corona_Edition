#include "../../includes/doom.h"

void		set_floor_limit(t_doom *doom, t_plane *plane, t_sidedef sidedef,\
			t_sector *sector)
{
	double	height_floor;
	double	plane_height_std;
	int		new_height;
	int		plane_bottom;

	if (doom->i_sector == sector->id)
		sector->floor_end = HEIGHT;
	else
	{
		new_height = (HEIGHT / 2) + doom->player_height;
		plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
			* doom->dist_to_plane;
		plane_height_std = plane_height_std / 2;
		height_floor = (sector->height_floor)\
			/ sidedef.prev_sidedef.distance * doom->dist_to_plane;
		plane_bottom = (new_height + plane_height_std) - \
			doom->own_event.y_pitch - height_floor + 1;
		plane_bottom = ((plane_bottom < HEIGHT ? plane_bottom : (HEIGHT)));
		if (plane_bottom <= plane->sidedef_bottom)
			plane_bottom = HEIGHT;
		else if (plane_bottom < 0)
			plane_bottom = 0;
		sector->floor_end = plane_bottom;
	}
}
