/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_skybox.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 11:14:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/09 12:40:19 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"




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

static void		draw_side_textures(t_doom *doom, t_plane plane, int offset, t_point pixel, Uint32 tex_dex)
{
	Uint32	pixel_dex;
	Uint32	index;
	double	wall_y;
	int		bpp;

	// printf("side: %d\n", sidedef.id);
	bpp = doom->surface->format->BytesPerPixel;
	index = (pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((int)(pixel.y + plane.wall_offset) - plane.sidedef_top) * 8;
	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->lib.sky_lib[tex_dex]->pitch) +\
		((int)offset * bpp) * 8;
	put_sky(doom, tex_dex, index, pixel_dex);
}

int		set_offset(t_line line, t_point intersect, t_doom *doom, int *dir)
{
	t_point start;
	t_point end;
	Uint8	diff;
	int		offset;

	start = line.start;
	end = line.end;
	diff = find_slope_line_offset(start, end);
	if (start.x == end.x || diff == 1)
	{
		offset = ft_rounder(intersect.y) % doom->wall_height_std;
		*dir = 0;
	}
	else if (start.y == end.y || diff == 2)
	{
		offset = ft_rounder(intersect.x) % doom->wall_height_std;
		*dir = 1;
	}
	return (offset);
}

void		find_side(t_doom *doom, int x, t_line line, t_plane plane, t_point intersect)
{
	t_point	pixel;
	Uint32	tex_dex;
	double	dir_angle;
	int		offset;
	int 	dir;

	pixel.x = x;
	pixel.y = plane.sidedef_top;
	offset = set_offset(line, intersect, doom, &dir);
	while (pixel.y < plane.sidedef_bottom)
	{
		dir_angle = doom->dir_angle;
		if ((dir_angle > PI / 2 && dir_angle < (3 * PI) / 2)\
		&& dir == 0)
			tex_dex = 2;
		else if ((dir_angle > (3 * PI) / 2 || dir_angle < PI / 2)\
		&& dir == 0)
			tex_dex = 4;
		else if (dir_angle > PI && dir_angle <= 2 * PI && dir == 1)
			tex_dex = 3;
		else
			tex_dex = 5;
		draw_side_textures(doom, plane, offset, pixel, tex_dex);
		pixel.y++;
	}
}

