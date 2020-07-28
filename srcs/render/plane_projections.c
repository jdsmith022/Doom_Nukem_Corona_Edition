#include "../../includes/doom.h"

static void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					t_sector *opp_sector, t_plane *plane)
{
	double		height_opp_sector;
	double		height_floor;
	int			mid_top;
	int			mid_bottom;
	int			div_height_std;
	int			new_height;

	new_height = (HEIGHT / 2) + doom->player_height;
	div_height_std = plane->height_standard / 2 + opp_sector->height_ceiling;
	height_opp_sector = opp_sector->height_ceiling / sidedef.distance * doom->dist_to_plane;
	mid_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	if (opp_sector->slope_id != -1)
	{
		opp_sector->slope = set_properties_slope(doom, sidedef, opp_sector);
		opp_sector->height_floor += opp_sector->slope.height;
	}
	height_floor = opp_sector->height_floor / sidedef.distance * doom->dist_to_plane;
	mid_bottom = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ?\
		mid_bottom : (HEIGHT));
}

static void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	int			new_height;

	(void)sector;
	new_height = (HEIGHT / 2) + doom->player_height;
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2 + sector->height_ceiling;
	// height_sidedef = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	if (sector->slope_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		set_slope_bottom_values(doom, sidedef, sector);
		sector->height_floor += sector->slope.height;
	}
	height_floor = sector->height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

static void		set_properties_plane(t_doom *doom, t_sidedef sidedef,\
					t_plane *plane, t_sector *sector)
{
	t_sector opp_sector;

	ft_bzero(plane, sizeof(plane));
	set_properties_plane_sidedef(doom, sidedef, sector, plane);
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
	if (sector->slope_id != -1)
		sector->slope.delta_height = set_slope_delta(doom, sector, plane->sidedef_bottom);
}

int		project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
	plane.intersect = sidedef.intersect;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sidedef.prev_sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	set_properties_plane(doom, sidedef, &plane, &sector);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (!sector.outside)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	if (!sector.outside)
		draw_floor(doom, x, sector, plane.sidedef_bottom);
	if (sidedef.poster != -1)
	{
		doom->texture_height = 16;
		doom->texture_width = 16;
		doom->distance = sidedef.distance;
		plane.intersect = doom->lib.sidedef[sidedef.poster].intersect;
		set_properties_plane(doom, doom->lib.sidedef[sidedef.poster], &plane, &sector);
		// doom->lib.sidedef[sidedef.poster].offset = sidedef.offset;
		draw_onesided_sidedef(doom, plane, doom->lib.sidedef[sidedef.poster], x);
		doom->texture_height = 96;
		doom->texture_width = 96;
	}
	return (0);
}
