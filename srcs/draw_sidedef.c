/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 18:40:59 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 21:13:51 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/doom.h"

void		put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[(y * WIDTH) + x] = (Uint32)color;
}

void		draw_sidedef(t_doom *doom, t_sidedef sidedef, int x)
{
	int		y;
	int 	id;
	int 	sidedef_height;
	int		sidedef_top;
	int		sidedef_bottom;


	y = 0;
	id = sidedef.sector;
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sidedef_height = doom->sector[0].height_ceiling - doom->sector[0].height_floor;
	sidedef_height = sidedef_height / sidedef.distance * doom->dist_to_plane;
	sidedef_top = HEIGHT / 2 - sidedef_height / 2;
	sidedef_bottom = HEIGHT / 2 + sidedef_height / 2;
	while (y < HEIGHT)
	{
		if (y <= sidedef_top)
			put_pixel(doom, x, y, 0x5B2C6F);
		else if (y > sidedef_top && y < sidedef_bottom)
			put_pixel(doom, x, y, 0xdcedc1);
		else
			put_pixel(doom, x, y, 0xffa500);	
		y++;
	}
}