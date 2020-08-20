#include "../../includes/doom.h"

// static void		find_poster_coords(t_doom *doom, t_plane *plane, t_sidedef sidedef, t_sector sector)
// {
// 	int	poster_top;
// 	int poster_bottom;
// 	int	poster_height;
// 	int height_ceiling;
// 	int	height_floor;
// 	double scale;
// 	t_plane plane;

	
// 	poster_height = 16 / sidedef.distance * doom->dist_to_plane;
// 	scale = poster_height / doom->texture_height;
// 	// poster_top = PLAYER_HEIGHT + (height_floor - doom->own_event.y_pitch);
// 	poster_bottom = ((HEIGHT / 2)  //+ ((doom->player_height) * scale)) - (doom->own_event.y_pitch + height_floor) - PLAYER_HEIGHT;
// 	// poster_bottom = poster_top + poster_size - (doom->own_event.y_pitch + height_floor);
// 	poster_top = poster_bottom - poster_size;
// 	plane->sidedef_top = poster_top;
// 	plane->sidedef_bottom = poster_bottom;
// 	// if (poster_top > height_ceiling && poster_bottom < height_floor)
// 	printf("top: %d --- bottom: %d --- ceiling: %d floor: %d ---- poster: %d\n", poster_top, poster_bottom, height_ceiling, height_floor, poster_size);
// }


void			draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_sector	sector;
	double		poster_height;

	sector = doom->lib.sector[sidedef.sector];
	plane.x = x;
	doom->distance = sidedef.distance;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sector.height_floor = PLAYER_HEIGHT - 16;
	sector.height_ceiling = -40;
	set_properties_plane_sidedef(doom, \
		sidedef, sector, &plane);
	doom->texture_height = 16;
	doom->texture_width = 16;
	// find_poster_coords(doom, &plane, sidedef, sector);
	printf("id = %d,, text = %d\n", sidedef.id, sidedef.txt_2);
	plane.intersect = doom->lib.sidedef[sidedef.poster].intersect;
	draw_onesided_sidedef(doom, plane, sidedef, x);
	doom->texture_height = 96;
	doom->texture_width = 96;
}
