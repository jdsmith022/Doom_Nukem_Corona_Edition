/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_column.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou          #+#    #+#                */
/*   Updated: 2020/04/01 20:43:23 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	pixels[(y * WIDTH) + x] = (Uint32)color;
}

void 		draw(t_doom *doom, t_column wall, int x)
{
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y <= wall.y_start)
			put_pixel(doom, x, y, 0x5B2C6F);
		else if (y > wall.y_start && y < wall.y_end)
			put_pixel(doom, x, y, 0xdcedc1);
		else
			put_pixel(doom, x, y, 0xffa500);	
		y++;
	}
}

void		draw_column(t_doom *doom, t_intersect intersect, int x)
{
	int collum_wall_height;
	int	wall_height;
	t_column wall;

	intersect.obj_dist *= cos(doom->ray_angle * x - FOV / 2);
	wall_height = doom->sector_1.height_ceiling - doom->sector_1.height_floor;
	collum_wall_height = wall_height / intersect.obj_dist * doom->dist_to_plane;
	wall.y_start = HEIGHT / 2 - collum_wall_height / 2;
	wall.y_end = HEIGHT / 2 + collum_wall_height / 2;
	draw(doom, wall, x);
}