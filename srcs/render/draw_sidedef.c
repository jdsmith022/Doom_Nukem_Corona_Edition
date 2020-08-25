
#include "../../includes/doom.h"

void			put_portal_pixel(t_doom *doom, t_point pixel,
					int tint, int mask)
{
	Uint32	*pixels;
	Uint32	color;

	pixels = doom->surface->pixels;
	color = pixels[((int)pixel.y * WIDTH) + (int)pixel.x];
	if (tint != 0)
		add_tint_to_color(&color, tint, mask);
	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
		pixels[((int)pixel.y * WIDTH) + (int)pixel.x] = color;
}

static Uint32	find_sidedef_texture(t_doom *doom, t_sidedef sidedef,
					t_point pixel, t_plane plane)
{
	Uint32 tex_dex;

	if (sidedef.opp_sector == -1)
		tex_dex = sidedef.txt_2;
	else if (pixel.y <= plane.mid_texture_top)
		tex_dex = sidedef.txt_1;
	else if (pixel.y >= plane.mid_texture_bottom)
		tex_dex = sidedef.txt_3;
	return (tex_dex);
}

static void		find_texture_index(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
	Uint32	pixel_dex;
	Uint32	index;
	Uint32	tex_dex;
	double	wall_y;
	int		bpp;

	tex_dex = find_sidedef_texture(doom, sidedef, pixel, plane);
	bpp = doom->surface->format->BytesPerPixel;
	index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	if (wall_y > doom->texture_height)
		wall_y -= doom->texture_height;
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	put_texture(doom, tex_dex, index, pixel_dex);
}

void			draw_portal_sidedef(t_doom *doom, t_plane plane,
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
		if (pixel.y < plane.mid_texture_bottom)
			put_portal_pixel(doom, pixel, 0, WINDOW_MASK);
		if (pixel.y < plane.mid_texture_top ||\
		pixel.y > plane.mid_texture_bottom)
			find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}

void			draw_onesided_sidedef(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_point	pixel;
	char	*pixels;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	while (pixel.y < plane.sidedef_bottom)
	{
		add_light_to_pixel(doom, doom->lib.sector[sidedef.sector], x, pixel.y);
		find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}
