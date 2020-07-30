#include "../../includes/doom.h"

int		set_floor_limit(t_doom *doom, t_plane *plane, t_sidedef sidedef,\
			t_sector *sector)
{
	int		bottom;
	double	height_floor;
	int		new_height;
	int		plane_bottom;
	double	plane_height_std;

	if (doom->i_sector == sector->id)
		return (HEIGHT);
	new_height = (HEIGHT / 2) + doom->player_height;
	plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
		* doom->dist_to_plane;
	plane_height_std = plane_height_std / 2 + sector->height_ceiling;
	height_floor = (sector->height_floor)\
		/ sidedef.prev_sidedef.distance * doom->dist_to_plane;
	plane_bottom = (new_height + plane_height_std) - height_floor;
	plane_bottom = ((plane_bottom < HEIGHT ? plane_bottom : (HEIGHT)));
	if (plane_bottom <= plane->sidedef_bottom)
		plane_bottom = HEIGHT;
	return (plane_bottom);
}
