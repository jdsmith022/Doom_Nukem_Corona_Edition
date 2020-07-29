#include "../../includes/doom.h"

void			draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
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