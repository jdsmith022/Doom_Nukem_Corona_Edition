/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_skybox_sidedefs.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:02 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:32:47 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void		put_sky(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex)
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

static void		draw_side_textures(t_doom *doom, t_plane plane, double offset,
					Uint32 tex_dex)
{
	Uint32	pixel_dex;
	Uint32	index;
	t_point pixel;
	double	wall_y;
	int		bpp;

	pixel.x = plane.intersect.x;
	pixel.y = plane.intersect.y;
	bpp = doom->surface->format->BytesPerPixel;
	index = (Uint32)(pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->cast.texture_height / plane.height_standard) *\
		((int)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->lib.sky_lib[tex_dex]->pitch) +\
		(offset * bpp);
	put_sky(doom, tex_dex, index, pixel_dex);
}

static int		set_offset_skybox(t_line line, t_point intersect, t_doom *doom,
					int *dir)
{
	t_point start;
	t_point end;
	Uint8	diff;
	double	offset;

	start = line.start;
	end = line.end;
	diff = find_slope_line_offset(start, end);
	if (start.x == end.x || diff == 1)
	{
		offset = ft_rounder(intersect.y) % doom->cast.texture_width;
		*dir = 0;
	}
	else if (start.y == end.y || diff == 2)
	{
		offset = ft_rounder(intersect.x) % doom->cast.texture_width;
		*dir = 1;
	}
	return (offset);
}

void			find_skybox_sidedef_texture(t_doom *doom, int x,
					t_plane plane)
{
	Uint32	tex_dex;
	double	dir_angle;
	int		offset;
	int		dir;

	offset = set_offset_skybox(plane.line, plane.intersect, doom, &dir);
	plane.intersect.x = x;
	plane.intersect.y = plane.sidedef_top;
	while (plane.intersect.y < plane.sidedef_bottom)
	{
		dir_angle = doom->cast.dir_angle;
		if ((dir_angle > PI / 2 && dir_angle < (3 * PI) / 2)\
		&& dir == 0)
			tex_dex = 1;
		else if ((dir_angle > (3 * PI) / 2 || dir_angle < (PI / 2))\
		&& dir == 0)
			tex_dex = 3;
		else if (dir_angle > PI && dir_angle < (2 * PI) && dir == 1)
			tex_dex = 2;
		else if ((dir_angle > 0 || dir_angle < PI) && dir == 1)
			tex_dex = 4;
		draw_side_textures(doom, plane, offset, tex_dex);
		plane.intersect.y++;
	}
}
