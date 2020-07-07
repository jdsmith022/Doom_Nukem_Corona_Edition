/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/04 14:39:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

// static void		put_dimishing_light(Uint32 *color, double dist)
// {
// 	*color = ((*color & 0xff) >> 24) * (int)dist << 24;
// 	*color = ((*color & 0x00ff) >> 16) * (int)dist << 16;
// 	*color = ((*color & 0x0000ff) >> 8) * (int)dist << 8;./
// }

static void		put_protal_pixel(t_doom *doom, t_point pixel)
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
	// else if (pixel.y > plane.mid_texture_top &&\
	// pixel.y < plane.mid_texture_bottom)
	// 	tex_dex = sidedef.txt_2;
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
	index = (pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->lib.tex_lib[tex_dex]->h / plane.height_standard) *\
		((int)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp);
	put_texture(doom, tex_dex, index, pixel_dex);
	//put_dimishing_lighting(&texure[pixel_dex], sidedef.distance)
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
		if (pixel.y < plane.mid_texture_bottom)
			put_protal_pixel(doom, pixel);
		if (pixel.y > plane.mid_texture_bottom)
			find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}

void			draw_onesided_sidedef(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_point	pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	while (pixel.y < plane.sidedef_bottom)
	{
		find_texture_index(doom, pixel, plane, sidedef);
		pixel.y++;
	}
}
