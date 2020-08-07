#include "../../includes/doom.h"

static void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					t_sector *opp_sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			mid_top;
	int			mid_bottom;
	int			new_height;

	new_height = (HEIGHT / 2) + doom->player_height;
	height_ceiling = opp_sector->height_ceiling / \
		sidedef.distance * doom->dist_to_plane;
	mid_top = (new_height - (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_ceiling;
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	if (opp_sector->slope_floor_id != -1 || opp_sector->slope_ceiling_id != -1)
	{
		opp_sector->slope = set_properties_slope(doom, sidedef, opp_sector);
		opp_sector->height_floor += opp_sector->slope.height;
	}
	height_floor = opp_sector->height_floor / \
		sidedef.distance * doom->dist_to_plane;
	mid_bottom = (new_height + (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_floor;
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT));
}

static void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			sidedef_top;
	int			sidedef_bottom;
	int			new_height;

	new_height = (HEIGHT / 2) + doom->player_height;
	plane->height_standard = doom->texture_height / \
		sidedef.distance * doom->dist_to_plane;
	height_ceiling = sector->height_ceiling / \
		sidedef.distance * doom->dist_to_plane;
	sidedef_top = (new_height - (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_ceiling;
	wall_offset(plane, sidedef_top);
	if (sector->slope_floor_id != -1 || sector->slope_ceiling_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		if (doom->i_sector != sector->id)
			set_slope_bottom_values(doom, sidedef, sector);
		sector->height_floor += sector->slope.height;
	}
	height_floor = sector->height_floor / \
		sidedef.distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + (plane->height_standard / 2)) - \
		doom->own_event.y_pitch - height_floor;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

void		set_properties_plane(t_doom *doom, t_sidedef sidedef,\
					t_plane *plane, t_sector *sector)
{
	t_sector opp_sector;

	ft_bzero(plane, sizeof(plane));
	ft_bzero(&sector->slope, sizeof(sector->slope));
	set_properties_plane_sidedef(doom, sidedef, sector, plane);
	// sector->floor_end = set_floor_limit(doom, plane, sidedef, sector);
	// sector->ceiling_end = set_ceiling_limit(doom, plane, sidedef, sector);
	if (sidedef.opp_sector != -1)
	{
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			&opp_sector, plane);
	}
	if (sector->outside)
	{
		doom->lib.portal_ceiling = plane->sidedef_top;
		doom->lib.portal_floor = plane->sidedef_bottom;
	}
	if ((sector->slope_floor_id != -1 && sector->slope.prev_floor_id != -1) || \
	(sector->slope_ceiling_id != -1 && sector->slope.prev_ceiling_id != -1))
		sector->slope.delta_height = set_slope_delta(doom, sector, plane->sidedef_bottom);
}

void		project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
	plane.intersect = sidedef.intersect;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sidedef.prev_sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sector.plane_x = x;
	set_properties_plane(doom, sidedef, &plane, &sector);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (!sector.outside)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	if (!sector.outside)
		draw_floor(doom, x, sector, plane.sidedef_bottom);
	doom->lib.sector[sidedef.sector].sidedef_bottom[x] = plane.sidedef_bottom;
	doom->lib.sector[sidedef.sector].sidedef_top[x] = plane.sidedef_top;
	if (sidedef.poster != -1)
		draw_poster(doom, plane, sidedef, x);
}
