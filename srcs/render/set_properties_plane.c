#include "../../includes/doom.h"

static int	set_plane_bottom(t_doom *doom, double scale,
				double distance, int sector_floor)
{
	double	height_floor;
	int		sidedef_bottom;

	height_floor = sector_floor / distance * doom->dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + (doom->player_height * scale)) \
		- (doom->own_event.y_pitch + height_floor);
	if (sidedef_bottom < 0)
		sidedef_bottom = 0;
	else if (sidedef_bottom > HEIGHT)
		sidedef_bottom = HEIGHT;
	return (sidedef_bottom);
}

static int	set_plane_top(t_doom *doom, double scale,
				double distance, int sector_ceiling)
{
	double	height_ceiling;
	int		sidedef_top;
	int		diff;

	diff = STD_TEXT - doom->player_height;
	height_ceiling = sector_ceiling / distance * doom->dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - (diff * scale)) \
		- (doom->own_event.y_pitch + height_ceiling);
	return (sidedef_top);
}

void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
				t_sector opp_sector, t_plane *plane)
{
	double		scale;
	double		diff;

	if (opp_sector.slope_floor_id != -1)
		set_slope_height(doom, sidedef, opp_sector);
	diff = doom->texture_height - doom->player_height;
	plane->height_standard = doom->texture_height / \
		sidedef.distance * doom->dist_to_plane;
	scale = plane->height_standard / doom->texture_height;
	plane->mid_texture_top = \
		set_plane_top(doom, scale, sidedef.distance, opp_sector.height_ceiling);
	plane->mid_texture_bottom = \
	set_plane_bottom(doom, scale, sidedef.distance, opp_sector.height_floor);
}

void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		scale;

	if (sector.slope_floor_id != -1)
		sector.height_floor += set_slope_height(doom, sidedef, sector);
	plane->height_standard = \
		doom->texture_height / sidedef.distance * doom->dist_to_plane;
	scale = plane->height_standard / doom->texture_height;
	plane->sidedef_top = \
		set_plane_top(doom, scale, sidedef.distance, sector.height_ceiling);
	wall_offset(plane, plane->sidedef_top);
	plane->sidedef_bottom = \
		set_plane_bottom(doom, scale, sidedef.distance, sector.height_floor);
}
