#include "../../includes/doom.h"

void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					t_sector *opp_sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			mid_top;
	int			mid_bottom;
	int			new_height;

	if (opp_sector->slope_floor_id != -1)
		slope_plane_settings(doom, sidedef, opp_sector);
	new_height = (HEIGHT / 2) + doom->player_height;
	height_ceiling = opp_sector->height_ceiling / \
		sidedef.distance * doom->dist_to_plane;
	mid_top = ((new_height - (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_ceiling) + 2;
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	height_floor = opp_sector->height_floor / \
		sidedef.distance * doom->dist_to_plane;
	mid_bottom = ((new_height + (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_floor) - 2;
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT));
}

void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			sidedef_top;
	int			sidedef_bottom;
	int			new_height;

	if (sector->slope_floor_id != -1)
		slope_plane_settings(doom, sidedef, sector);
	new_height = (HEIGHT / 2) + doom->player_height;
	plane->height_standard = doom->texture_height / \
		sidedef.distance * doom->dist_to_plane;
	height_ceiling = sector->height_ceiling / \
		sidedef.distance * doom->dist_to_plane;
	sidedef_top = ((new_height - (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_ceiling);
	wall_offset(plane, sidedef_top);
	height_floor = sector->height_floor / \
		sidedef.distance * doom->dist_to_plane;
	sidedef_bottom = ((new_height + (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_floor);
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}
