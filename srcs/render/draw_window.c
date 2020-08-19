#include "../../includes/doom.h"

static void		put_window_texture(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
	Uint32	pixel_dex;
	Uint32	index;
	Uint32	tex_dex;
	double	wall_y;
	int		bpp;
	char	*textures;

	tex_dex = sidedef.txt_2;
	textures = doom->lib.tex_lib[tex_dex]->pixels;
	if (textures[pixel_dex] == (char)255 && \
	textures[pixel_dex + 1] == (char)255 &&\
	textures[pixel_dex + 2] == (char)255)
		put_portal_pixel(doom, pixel);
	else
	{
		// printf("")
		bpp = doom->surface->format->BytesPerPixel;
		index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
		wall_y = (double)(doom->texture_height / plane.height_standard) *\
			((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
		if (wall_y > doom->texture_height)
			wall_y -= doom->texture_height;
		bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
		pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
			(sidedef.offset * bpp));
		// printf("put text %f, %f --- texdex: %d --- index: %d ---- pixeldex: %d\n", pixel.x, pixel.y, tex_dex, index, pixel_dex);
		put_texture(doom, tex_dex, index, pixel_dex);
	}
}

void			doom_lights(t_doom *doom, t_sidedef sidedef, int x)
{
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
		doom->distance = x > WIDTH / 2 ? \
			doom->distance - (x - (float)WIDTH / 2.0) * X_CHANGE :\
			+doom->distance - ((float)WIDTH / 2.0 - x) * X_CHANGE;
	}
}

void			draw_window(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	Uint32	*pixels;
	t_point	pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	pixels = doom->surface->pixels;
	doom_lights(doom, sidedef, x);
	while (pixel.y < plane.sidedef_bottom)
	{
		if (doom->light == FALSE)
			doom->distance = pixel.y > HEIGHT / 2 ?\
			doom->distance - Y_CHANGE : doom->distance + Y_CHANGE;
		put_window_texture(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}
