#include "../../includes/doom.h"

static void		set_sector_properties(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	t_sector opp_sector;

	if (sidedef.opp_sector != -1)
	{
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			&opp_sector, plane);
	}
	if (sector->action == 1)
		doom->lib.portal_ceiling = plane->sidedef_top;
}

void			set_properties_plane(t_doom *doom, t_sidedef sidedef,
					t_plane *plane, t_sector *sector)
{
	int x;

	x = sector->plane_x;
	ft_bzero(plane, sizeof(plane));
	ft_bzero(&sector->slope, sizeof(sector->slope));
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sidedef.prev_sidedef.distance *= \
		cos(doom->ray_adjacent * x - FOV / 2);
	*sector = doom->lib.sector[sidedef.sector];
	plane->intersect = sidedef.intersect;
	set_properties_plane_sidedef(doom, sidedef, sector, plane);
	set_floor_limit(doom, plane, sidedef, sector);
	set_ceiling_limit(doom, plane, sidedef, sector);
	set_sector_properties(doom, sidedef, sector, plane);
}

void				project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	sector.plane_x = x;
	set_properties_plane(doom, sidedef, &plane, &sector);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (sector.action != 1)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	draw_floor(doom, x, sector, plane.sidedef_bottom);
	doom->lib.sector[sidedef.sector].sidedef_bottom[x] = plane.sidedef_bottom;
	doom->lib.sector[sidedef.sector].sidedef_top[x] = plane.sidedef_top;
	if (sidedef.poster != -1)
		draw_poster(doom, plane, sidedef, x);
}
