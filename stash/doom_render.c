/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 16:54:18 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/09 14:50:00 by rooscocolie   ########   odam.nl         */
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
	t_ray 	ray;
	int			player_height;

	x = 0;
	doom->angle = doom->dir_angle - (FOV / 2);
	ray.line.start = doom->pos;
	player_height = doom->player_height;
	doom->player_height += doom->sector[doom->i_sector].height_floor;
	while (x < WIDTH)
	{
		doom->angle = clamp_angle(doom->angle);
		ray.angle = doom->angle;
		ray.line.end.x = ray.line.start.x + doom->max_ray * cos(doom->angle);
		ray.line.end.y = ray.line.start.y + doom->max_ray * sin(doom->angle);
		
		ray.plane_x = x;
		sidedef_render(doom, ray, doom->i_sector, doom->i_sector);
		doom->angle += doom->ray_adjacent;
		x++;
	}
	doom->player_height = player_height;
}
