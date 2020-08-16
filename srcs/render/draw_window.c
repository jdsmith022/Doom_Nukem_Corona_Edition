#include "../../includes/doom.h"

// static int		portal_wall(t_doom *doom, t_point pixel, Uint32 pixel_dex, Uint32 tex_dex)
// {
// 	Uint32 *texture;

// 	texture = doom->lib.tex_lib[tex_dex]->pixels;
// 	if (texture[pixel_dex] == (char)255 && texture[pixel_dex  + 1] == (char)255 &&\
// 	texture[pixel_dex + 2]== (char)255 && doom->lib.sidedef[doom->i_sidedef].action == 6)
// 	{
// 		put_portal_pixel(doom, pixel);
// 		return (-1);
// 	}
// 	return (1);
// }

static void		put_portal_pixel(t_doom *doom, t_point pixel)
{
	Uint32	*pixels;
	Uint32	color;

	pixels = doom->surface->pixels;
	color = pixels[((int)pixel.y * WIDTH) + (int)pixel.x];
	pixels = doom->surface->pixels;
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


static void		find_texture(t_doom *doom, t_point pixel, t_plane plane,
					t_sidedef sidedef)
{
	Uint32	pixel_dex;
	Uint32	index;
	Uint32	tex_dex;
	double	wall_y;
	int		bpp;
	char  	*textures;

	tex_dex = find_sidedef_texture(doom, sidedef, pixel, plane);
	textures = doom->lib.tex_lib[tex_dex]->pixels;
	bpp = doom->surface->format->BytesPerPixel;
	index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	if (wall_y > doom->texture_height)
		wall_y -= doom->texture_height;
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	if (textures[pixel_dex] == (char)255 && textures[pixel_dex  + 1] == (char)255 &&\
	textures[pixel_dex + 2] == (char)255)
		put_portal_pixel(doom, pixel);
	else
		put_texture(doom, tex_dex, index, pixel_dex);
	// put_dimishing_lighting(&texure[pixel_dex], sidedef.distance)
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
		find_texture(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}
