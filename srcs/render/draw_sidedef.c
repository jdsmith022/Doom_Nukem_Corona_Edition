/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:01:56 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 20:13:26 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void			put_portal_pixel(t_doom *doom, t_point pixel,
					int tint, int mask)
{
	Uint32	*pixels;
	Uint32	color;

	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
	{
		pixels = doom->surface->pixels;
		color = pixels[((int)pixel.y * WIDTH) + (int)pixel.x];
		if (tint != 0)
			add_tint_to_color(&color, tint, mask);
		pixels[((int)pixel.y * WIDTH) + (int)pixel.x] = color;
	}
}

static void		find_texture_index(t_doom *doom, t_point pixel, t_plane plane,
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
	wall_y = (double)(doom->cast.texture_height / plane.height_standard) *\
		((double)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	if (wall_y > doom->cast.texture_height)
		wall_y -= doom->cast.texture_height;
	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = (((int)wall_y * doom->lib.tex_lib[tex_dex]->pitch) +\
		(sidedef.offset * bpp));
	put_texture(doom, tex_dex, index, pixel_dex);
}

static void		put_texture_sidedef(t_doom *doom, t_sidedef sidedef,
					t_plane plane, t_point pixel)
{
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
	add_light_to_pixel(doom, sector, pixel.x, pixel.y);
	find_texture_index(doom, pixel, plane, sidedef);
}

void			draw_portal_sidedef(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	Uint32		*pixels;
	t_point		pixel;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	pixels = doom->surface->pixels;
	if (doom->game.light == FALSE && \
	doom->lib.sector[sidedef.sector].action != OUTSIDE)
		calculate_ceiling_dist(doom, pixel.x, pixel.y, doom->lib.sector[sidedef.sector]);
	while (pixel.y < plane.mid_texture_top)
	{
		sidedef.txt_2 = sidedef.txt_1;
		put_texture_sidedef(doom, sidedef, plane, pixel);
		pixel.y++;
	}
	while (pixel.y < plane.mid_texture_bottom && pixel.y < HEIGHT)
	{
		put_portal_pixel(doom, pixel, 0, WINDOW_MASK);
		pixel.y++;
	}
	while (pixel.y < plane.sidedef_bottom && pixel.y < HEIGHT)
	{
		sidedef.txt_2 = sidedef.txt_3;
		put_texture_sidedef(doom, sidedef, plane, pixel);
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
	if (doom->game.light == FALSE && \
	doom->lib.sector[sidedef.sector].action != OUTSIDE && \
	sidedef.action != 4 && sidedef.action != 8)	
		calculate_ceiling_dist(doom, pixel.x, pixel.y, \
		doom->lib.sector[sidedef.sector]);
	while (pixel.y < plane.sidedef_bottom)
	{
		put_texture_sidedef(doom, sidedef, plane, pixel);
		pixel.y++;
	}
}
