#include "../../includes/doom.h"

static int	set_plane_bottom(t_doom *doom, double scale,
				t_sidedef sidedef, t_sector sector)
{
	double	height_floor;
	int		sidedef_bottom;

	if (sector.slope_floor_id != -1)
		sector.height_floor += set_slope_height_floor(doom, sidedef, sector);
	height_floor = sector.height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + (doom->player_height * scale)) \
		- (doom->own_event.y_pitch + height_floor);
	if (sidedef_bottom < 0)
		sidedef_bottom = 0;
	else if (sidedef_bottom > HEIGHT)
		sidedef_bottom = HEIGHT;
	return (sidedef_bottom);
}

static int	set_plane_top(t_doom *doom, double scale,
				t_sidedef sidedef, t_sector sector)
{
	double	height_ceiling;
	int		sidedef_top;
	int		diff;

	if (sidedef.poster == -1)
		diff = doom->texture_height - doom->player_height;
	else
		diff = STD_TEXT_HEIGHT - doom->player_height;
	if (sector.slope_ceiling_id != -1)
		sector.height_ceiling -= \
			set_slope_height_ceiling(doom, sidedef, sector);
	height_ceiling = sector.height_ceiling / \
		sidedef.distance * doom->dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - (diff * scale)) \
		- (doom->own_event.y_pitch + height_ceiling);
	return (sidedef_top);
}

void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
				t_sector opp_sector, t_plane *plane)
{
	double		scale;

	plane->height_standard = doom->texture_height / \
		sidedef.distance * doom->dist_to_plane;
	scale = plane->height_standard / doom->texture_height;
	plane->mid_texture_top = \
		set_plane_top(doom, scale, sidedef, opp_sector);
	plane->mid_texture_bottom = \
		set_plane_bottom(doom, scale, sidedef, opp_sector);
}

void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		scale;

	plane->height_standard = \
		doom->texture_height / sidedef.distance * doom->dist_to_plane;
	scale = plane->height_standard / doom->texture_height;
	plane->sidedef_top = \
		set_plane_top(doom, scale, sidedef, sector);
	wall_offset(plane, plane->sidedef_top);
	plane->sidedef_bottom = \
		set_plane_bottom(doom, scale, sidedef, sector);
}
