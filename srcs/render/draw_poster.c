#include "../../includes/doom.h"

static void		poster_resize(t_doom * doom, t_plane *plane)
{
	int poster_len;
	int	start;
	int end;

	poster_len = (plane->sidedef_bottom - plane->sidedef_top) / 5;
	poster_len /= 2;
	start = (plane->sidedef_bottom - plane->sidedef_top) / 2 - poster_len;
	plane->sidedef_top = start;
	end = (plane->sidedef_bottom - plane->sidedef_top) / 2 + poster_len;
	plane->sidedef_bottom = end;
}

void			draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
	doom->texture_height = 16;
	doom->texture_width = 16;
	sector.plane_x = x;
	doom->distance = sidedef.distance;
	plane.intersect = doom->lib.sidedef[sidedef.poster].intersect;
	poster_resize(doom, &plane);
	set_properties_plane(doom, \
		doom->lib.sidedef[sidedef.poster], &plane, &sector);
	draw_onesided_sidedef(doom, plane, doom->lib.sidedef[sidedef.poster], x);
	doom->texture_height = 96;
	doom->texture_width = 96;
}
