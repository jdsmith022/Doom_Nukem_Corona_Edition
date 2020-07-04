/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 16:07:32 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/04 15:40:45 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		sprite_check(t_doom *doom, t_ray ray)
{
	//check line intersection with all not yet visible sprites
	int		i;
	t_point	ray_delta;
	t_point sprite_delta;
	t_point intersect;

	i = 0;
	//TOTAL_SPRITES in sector
	while (i < TOTAL_SPRITE && doom->sprite[i].visible != 1)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(doom->sprite[i].line.start, doom->sprite[i].line.end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		doom->sprite[i].line.start, sprite_delta);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			printf("intersect x: %f\n", intersect.x);
			printf("intersect y: %f\n", intersect.y);
			doom->visible_sprites++;
			doom->sprite[i].visible = 1;
			doom->sprite[i].distance = point_distance(doom->pos, doom->sprite[i].pos, ray.angle);
			printf("sprite %d is visible\ndistance to player: %f\n", i, doom->sprite[i].distance);
		}
		i++;
	}
}
