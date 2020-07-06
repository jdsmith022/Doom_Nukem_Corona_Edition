/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_skybox.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 11:14:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/06 16:18:16 by jessicasmit   ########   odam.nl         */
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

static void		draw_side_textures(t_doom *doom, t_plane plane,
					t_sidedef sidedef, t_point pixel, Uint32 tex_dex)
{
	Uint32	pixel_dex;
	Uint32	index;
	double	wall_y;
	int		bpp;

	bpp = doom->surface->format->BytesPerPixel;
	// pixel.x += doom->pos.x;
	// pixel.y += doom->pos.y;
	// pixel.x = (int)pixel.x % doom->lib.sky_lib[tex_dex]->w;
	// pixel.y = (int)pixel.y % doom->lib.sky_lib[tex_dex]->h;
	index = (pixel.y * doom->surface->pitch) + (int)(pixel.x * bpp);
	wall_y = (double)(doom->texture_height / plane.height_standard) *\
		((int)(pixel.y + plane.wall_offset) - plane.sidedef_top);
	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	pixel_dex = ((int)wall_y * doom->lib.sky_lib[tex_dex]->pitch) +\
		((int)sidedef.offset * bpp);
	put_sky(doom, tex_dex, index, pixel_dex);
	//put_dimishing_lighting(&texure[pixel_dex], sidedef.distance)
}

static void		find_side(t_doom *doom, int x, t_sidedef sidedef,
					t_plane plane)
{
	t_point	pixel;
	t_point	start;
	t_point end;
	double	dir_angle;

	pixel.x = x;
	pixel.y = plane.sidedef_top;
	start = sidedef.line.start;
	end = sidedef.line.end;
	// printf("doom->ray_dir_angle: %f\n", doom->dir_angle);
		printf("sidedef.dir= %d\n", sidedef.dir);
	while (pixel.y <= plane.sidedef_bottom)
	{
		dir_angle = doom->dir_angle;
		// dir_angle *= PI / 180;
		if (dir_angle >= 0 && dir_angle <= PI / 2 && sidedef.dir == 1)
			draw_side_textures(doom, plane, sidedef, pixel, 2);
		else if (dir_angle > PI / 2 && dir_angle < PI && sidedef.dir == 0)
			draw_side_textures(doom, plane, sidedef, pixel, 3);
		else if (dir_angle >= PI && dir_angle <= (3 * PI) / 2 && sidedef.dir == 1)
			draw_side_textures(doom, plane, sidedef, pixel, 1);
		else if (dir_angle > (3 * PI) / 2 && dir_angle < 2 * PI && sidedef.dir == 0)
			draw_side_textures(doom, plane, sidedef, pixel, 5);
		pixel.y++;
	}
}

static void		put_row(t_doom *doom, Uint32 tex_dex,
					Uint32 index, Uint64 pixel_dex)
{
	char *pixels;
	char *texture;

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

static void		row_calculations(t_doom *doom, double dist, Uint32 index,
					Uint32 tex_dex)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	// floor.x -= doom->pos.x;
	// floor.y -= doom->pos.y;
	texture.x = (int)floor.x % doom->lib.sky_lib[tex_dex]->w;
	texture.y = (int)floor.y % doom->lib.sky_lib[tex_dex]->h;
	pixel_dex = (((int)texture.y * doom->lib.sky_lib[tex_dex]->pitch)\
		+ ((int)texture.x * bpp));
	put_row(doom, tex_dex, index, pixel_dex);
}

void			draw_ground(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint32	tex_dex;
	Uint8	bpp;

	tex_dex = 1;
	height = HEIGHT / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (y - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}

static void		draw_sky(t_doom *doom, int x, t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint32	height;
	Uint8	bpp;

	tex_dex = 5;
	bpp = doom->surface->format->BytesPerPixel;
	height = HEIGHT / 2;
	while (y >= 0)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (height - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, index, tex_dex);
		y--;
	}
}

void	draw_skybox(t_doom *doom, int x, t_sidedef sidedef, t_plane plane)
{
	t_sector sector;

	sector = doom->lib.sector[sidedef.sector];
	draw_sky(doom, x, sector, plane.sidedef_top);
	find_side(doom, x, sidedef, plane);
	draw_ground(doom, x, sector, plane.sidedef_bottom);
}
