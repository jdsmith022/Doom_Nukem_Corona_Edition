#include "../../includes/doom.h"


static void		set_properties_plane_poster(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	int			new_height;

	(void)sector;
	new_height = (HEIGHT + doom->player_height) / 2;
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	// height_sidedef = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	height_floor = sector.height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

static void		find_poster_index(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
		Uint32	pixel_dex;
	Uint32	index;
	Uint32	tex_dex;
	double	wall_y;
	int		bpp;

	tex_dex = sidedef.txt_2;
	bpp = doom->surface->format->BytesPerPixel;
	index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	put_texture(doom, tex_dex, index, pixel_dex);
}

void			draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_point	pixel;
	char	*pixels;
    int     bottom;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
    if (doom->light == TRUE)
	{
		if (doom->lib.sector[sidedef.sector].light == TRUE)
			doom->distance = doom->lib.sector[sidedef.sector].light_level;
		else
			doom->distance = 0.15;
	}
	else
	{
		doom->distance = 1 / (doom->distance / 70);
		doom->distance = x > WIDTH / 2 ? doom->distance - (x - (float)WIDTH / 2.0) * X_CHANGE : + doom->distance - ((float)WIDTH / 2.0 - x) * X_CHANGE;
	}
	while (pixel.y <  plane.sidedef_bottom)
	{
		if (doom->light == FALSE)
			doom->distance = pixel.y > HEIGHT / 2 ? doom->distance - Y_CHANGE : doom->distance + Y_CHANGE;
		find_poster_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}