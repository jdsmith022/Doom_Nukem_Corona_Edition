/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 16:54:18 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/07 14:17:42 by jessicasmit   ########   odam.nl         */
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
	int		sky;

	x = 0;
	ray.angle = doom->dir_angle - (FOV / 2);
	if (doom->lib.sector[doom->i_sector].outside)
	{
		ray.line.start.x = 64;
		ray.line.start.y = 64;
	}
	else
		ray.line.start = doom->pos;
	while (x < WIDTH)
	{
		ray.angle = clamp_angle(ray.angle);
		doom->ray_angle = ray.angle;
		ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
		ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
		ray.plane_x = x;
		sky = sidedef_render(doom, ray, doom->i_sector, doom->i_sector);
		if (sky == 1)
		{
			ray.line.start = doom->pos;
			ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
			ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
			sidedef_render(doom, ray, doom->i_sector + 1, doom->i_sector + 1);
		}
		if (doom->lib.sector[doom->i_sector].outside)
		{
			ray.line.start.x = 64;
			ray.line.start.y = 64;
		}
		ray.angle += doom->ray_adjacent;
		x++;
	}
}
