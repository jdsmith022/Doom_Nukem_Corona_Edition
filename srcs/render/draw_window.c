/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 23:47:17 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

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
	wall_y = (double)(doom->cast.texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	if (wall_y > doom->cast.texture_height)
		wall_y -= doom->cast.texture_height;
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	put_window_pixel(doom, pixel, tex_dex, pixel_dex);
}

void			save_window(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	doom->own_event.window = TRUE;
	if (doom->lib.window.x_start == -1)
	{
		doom->lib.window.index = sidedef.id;
		doom->lib.window.x_start = x;
		doom->lib.window.opp_sector = sidedef.opp_sector;
		doom->lib.window.curr_sector = sidedef.sector;
	}
	else if (doom->lib.window.x_end == WIDTH + 1 ||\
		x > doom->lib.window.x_start)
		doom->lib.window.x_end = x;
	doom->lib.window.y_pixel_top[x] = plane.sidedef_top;
	doom->lib.window.y_pixel_bottom[x] = plane.sidedef_bottom;
	doom->lib.window.height_standard[x] = plane.height_standard;
	doom->lib.window.wall_offset[x] = plane.wall_offset;
	doom->lib.window.sidedef_offset[x] = sidedef.offset;
}

static void		calculate_window_pixels(t_doom *doom, t_point pixel,
					t_plane plane, int x)
{
	add_light_to_pixel(doom,\
	doom->lib.sector[doom->lib.window.curr_sector], pixel.x, pixel.y);
	doom->lib.sidedef[doom->lib.window.index].offset =\
	doom->lib.window.sidedef_offset[x];
	put_window_texture(doom, pixel, plane,\
	doom->lib.sidedef[doom->lib.window.index]);
}

void			draw_window_as_sprite(t_doom *doom)
{
	Uint32	*pixels;
	t_point	pixel;
	int		x;
	t_plane	plane;

	x = doom->lib.window.x_start;
	while (x <= doom->lib.window.x_end)
	{
		plane.height_standard = doom->lib.window.height_standard[x];
		plane.wall_offset = doom->lib.window.wall_offset[x];
		plane.sidedef_top = doom->lib.window.y_pixel_top[x];
		pixel.y = doom->lib.window.y_pixel_top[x];
		pixel.x = x;
		pixels = doom->surface->pixels;
		calculate_ceiling_dist(doom, pixel.x, pixel.y, \
			doom->lib.sector[doom->lib.window.curr_sector]);
		while (pixel.y < doom->lib.window.y_pixel_bottom[x])
		{
			calculate_window_pixels(doom, pixel, plane, x);
			pixel.y++;
		}
		x++;
	}
	init_window(doom);
}
