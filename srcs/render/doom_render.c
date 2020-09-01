/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:01:21 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:34:06 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

double			clamp_angle(double angle)
{
	if (angle > 360 * (PI / 180))
		angle -= 360 * (PI / 180);
	else if (angle < 0)
		angle += 360 * (PI / 180);
	return (angle);
}

t_ray			init_ray(t_doom *doom, int x)
{
	t_ray	ray;

	ray.angle = \
		clamp_angle(doom->cast.dir_angle - \
		((60 * (PI / 180)) / 2) + doom->cast.ray_adjacent * x);
	ray.line.start = doom->pos;
	ray.line.end.x = ray.line.start.x + doom->cast.max_ray * cos(ray.angle);
	ray.line.end.y = ray.line.start.y + doom->cast.max_ray * sin(ray.angle);
	ray.plane_x = x;
	return (ray);
}

void			doom_render(t_doom *doom)
{
	int		x;
	t_ray	ray;
	int		sky;

	x = 0;
	ray.angle = doom->cast.dir_angle - ((60 * (PI / 180)) / 2);
	ray.line.start = doom->pos;
	ray.filter = 0;
	doom->visible_sprites = 0;
	doom->cast.poster = set;
	while (x < WIDTH)
	{
		ray.angle = clamp_angle(ray.angle);
		doom->cast.ray_angle = ray.angle;
		ray.line.end.x = ray.line.start.x + doom->cast.max_ray * cos(ray.angle);
		ray.line.end.y = ray.line.start.y + doom->cast.max_ray * sin(ray.angle);
		ray.plane_x = x;
		sidedef_render(doom, ray, doom->i_sector, doom->i_sector);
		ray.angle += doom->cast.ray_adjacent;
		x++;
	}
	if (doom->visible_sprites > 0)
		sprite_render(doom);
}
