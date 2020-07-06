/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_skybox.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 11:14:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/06 15:43:40 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		put_sky(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint64 pixel_dex)
{
	char	*pixels;
	char	*texture;

	pixels = doom->surface->pixels;
	texture = doom->lib.sky_lib[tex_dex]->pixels;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
}

static void		draw_side_textures(t_doom *doom, t_plane plane,
					t_sidedef sidedef, t_point pixel, Uint32 tex_dex)
{
	Uint64	pixel_dex;
	Uint32	index;
	double	wall_y;
	int		bpp;

	bpp = doom->surface->format->BytesPerPixel;
	index = (pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((int)(pixel.y + plane.wall_offset) - plane.sidedef_top) * 8;
	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->lib.sky_lib[tex_dex]->pitch) +\
		((int)sidedef.offset * bpp) * 8;
	put_sky(doom, tex_dex, index, pixel_dex);
}

static void		find_side(t_doom *doom, int x, t_sidedef sidedef,
					t_plane plane)
{
	t_point	pixel;
	t_point	start;
	t_point end;
	Uint32	tex_dex;
	double	dir_angle;

	pixel.x = x;
	pixel.y = plane.sidedef_top;
	printf("sidedef.dir= %d	pos: %f, %f intersect: %f, %f\n", sidedef.dir, doom->pos.x, doom->pos.y, plane.intersect.x, plane.intersect.y);
	while (pixel.y <= plane.sidedef_bottom)
	{
		dir_angle = doom->dir_angle;
		if (plane.intersect.x > doom->pos.x && sidedef.dir == 0)
			tex_dex = 0;
		else if (plane.intersect.x < doom->pos.x && sidedef.dir == 0)
			tex_dex = 2;
		else if (plane.intersect.y > doom->pos.y && sidedef.dir == 1)
			tex_dex = 3;
		else
			tex_dex = 4;
		draw_side_textures(doom, plane, sidedef, pixel, tex_dex);
		pixel.y++;
	}
}



void	draw_skybox(t_doom *doom, int x, t_sidedef sidedef, t_plane plane)
{
	t_sector	sector;
	t_point		center;

	sector = doom->lib.sector[sidedef.sector];

	draw_sky(doom, x, sector, plane.sidedef_top);
	find_side(doom, x, sidedef, plane);
	draw_ground(doom, x, sector, plane.sidedef_bottom);
	// printf("finished\n");
}
