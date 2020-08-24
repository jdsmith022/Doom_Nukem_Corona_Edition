
#include "../../includes/doom.h"

static void		put_window_pixel(t_doom *doom, t_point pixel, Uint32 tex_dex,
					Uint32 pixel_dex)
{
	char	*textures;
	Uint32	index;
	int		bpp;

	bpp = doom->surface->format->BytesPerPixel;
	index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	textures = doom->lib.tex_lib[tex_dex]->pixels;
	if (textures[pixel_dex] == (char)255 && \
	textures[pixel_dex + 1] == (char)255 &&\
	textures[pixel_dex + 2] == (char)255)
		put_portal_pixel(doom, pixel, BLUE, WINDOW_MASK);
	else
		put_texture(doom, tex_dex, index, pixel_dex);
}

static void		put_window_texture(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
	Uint32	pixel_dex;
	Uint32	tex_dex;
	double	wall_y;
	int		bpp;

	tex_dex = sidedef.txt_2;
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	if (wall_y > doom->texture_height)
		wall_y -= doom->texture_height;
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	put_window_pixel(doom, pixel, tex_dex, pixel_dex);
}

void			draw_window(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	Uint32	*pixels;
	t_point	pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	pixels = doom->surface->pixels;
	while (pixel.y < plane.sidedef_bottom)
	{
		add_light_to_pixel(doom, doom->lib.sector[sidedef.sector], x, pixel.y);
		put_window_texture(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}
