/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 16:54:18 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/09 14:18:51 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
	t_ray	ray;

	x = 0;
	doom->ray_angle = doom->dir_angle - (FOV / 2);
	ray.line.start = doom->pos;
	while (x < WIDTH)
	{
		ray.angle = clamp_angle(ray.angle);
		doom->ray_angle = ray.angle;
		ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
		ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
		ray.plane_x = x;
		sidedef_render(doom, ray, doom->i_sector, doom->i_sector);
		doom->ray_angle += doom->ray_adjacent;
		x++;
	}
}
