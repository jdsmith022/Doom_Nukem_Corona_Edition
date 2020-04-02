/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 16:54:18 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 15:58:33 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


double			clamp_angle(double angle)
{
	if (angle > 360 * (PI / 180))
		angle -= 360 * (PI / 180);
	else if (angle < 0)
		angle += 360 * (PI / 180);
	return (angle);
}

void	doom_render(t_doom *doom)
{
	int		x;
	int		sector;
	t_line 	ray;

	x = 0;
	ray.angle = doom->dir_angle - (FOV / 2);
	ray.start = doom->pos;
	while (x < WIDTH)
	{
		ray.angle = clamp_angle(ray.angle);
		ray.end.x = ray.start.x + doom->max_ray * cos(ray.angle);
		ray.end.y = ray.start.y + doom->max_ray * sin(ray.angle);
		sector = doom->curr_sector;
		sidedef_render(doom, ray, sector, x);
		ray.angle += doom->ray_adjacent;
		x++;
	}

}