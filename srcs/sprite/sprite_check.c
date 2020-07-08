/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 16:07:32 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/08 17:18:11 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		sprite_check(t_doom *doom, t_ray ray, int sector)
{
	//check line intersection with all not yet visible sprites
	int		i;
	t_point	ray_delta;
	t_point sprite_delta;
	t_point intersect;

	i = doom->lib.sector[sector].i_objects;
	//TOTAL_SPRITES per sector
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprite[i].visible == 0)
		{
			//loop through every line of particular object, save closest distance and line segment
		}
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(doom->lib.sprite[i].lines->start, doom->lib.sprite[i].lines->end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		doom->lib.sprite[i].lines->start, sprite_delta);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			printf("intersect x: %f\n", intersect.x);
			printf("intersect y: %f\n", intersect.y);
			doom->visible_sprites++;
			doom->lib.sprite[i].visible = 1;
			doom->lib.sprite[i].distance = point_distance(doom->pos, doom->lib.sprite[i].pos, ray.angle);
			printf("sprite %d is visible\ndistance to player: %f\n", i, doom->lib.sprite[i].distance);
		}
		i++;
	}
}
