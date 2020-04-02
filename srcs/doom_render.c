/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 16:54:18 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 13:36:27 by Malou         ########   odam.nl         */
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
	double	angle;
	t_line ray;

	x = 0;
	angle = doom->dir_angle - (FOV / 2);
	ray.start = doom->pos;
	while (x < WIDTH)
	{
		angle = clamp_angle(angle);
		ray.end.x = ray.start.x + doom->max_ray * cos(angle);
		ray.end.y = ray.start.y + doom->max_ray * sin(angle);
		sidedef_render(doom, ray, angle, 1, x);
		angle += doom->ray_angle;
		x++;
	}

}