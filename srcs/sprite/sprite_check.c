/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 16:07:32 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/09 12:21:13 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		check_visibility_sprite(t_doom *doom, t_sprite *sprite, t_ray ray, int i)
{
	t_point	ray_delta;
	t_point sprite_delta;
	t_point intersect;
	double	curr_distance;
	double	temp_distance;

	temp_distance = INFINITY;
	curr_distance = 0;
	while (i < 4)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(sprite->lines[i].start, sprite->lines[i].end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		sprite->lines->start, sprite_delta);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			printf("intersect x: %f\n", intersect.x);
			printf("intersect y: %f\n", intersect.y);
			curr_distance = point_distance(doom->pos, intersect, ray.angle);
			if (curr_distance < temp_distance)
			{
				temp_distance = curr_distance;
				sprite->visible = i;
			}
			sprite->distance = point_distance(doom->pos, sprite->pos, ray.angle);
			printf("sprite %d is visible\ndistance to player: %f\n", i, sprite->distance);
		}
		i++;
	}
	if (sprite->visible != -1)
		doom->visible_sprites++;
}

void		sprite_check(t_doom *doom, t_ray ray, int sector)
{
	//check line intersection with all not yet visible sprites
	int		i;
	int		x;
	int		sprite_i;

	i = 0;
	x = 0;
	sprite_i = doom->lib.sector[sector].i_objects;
	//TOTAL_SPRITES per sector
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprite[sprite_i].visible == -1)
		{
			//loop through every line of particular object, save closest distance and line segment
			check_visibility_sprite(doom, &doom->lib.sprite[sprite_i], ray, x);
		}
		i++;
		sprite_i++;
	}
}
