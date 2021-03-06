/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:26 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/10 18:49:59 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		find_face_sprite(t_doom *doom, t_sprite *sprite, t_ray ray, int i)
{
	t_point		intersect;
	t_line		line_sprite;

	line_sprite.start = doom->pos;
	line_sprite.end = sprite->pos;
	while (i < 4)
	{
		intersect = sidedef_sprite_intersect(sprite->lines[i], line_sprite);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			sprite->visible = sprite->textures[i];
			sprite->distance = fabs(point_distance(doom->pos, sprite->pos));
		}
		i++;
	}
}

void		detect_sprite(t_doom *doom, t_sprite *sprite, t_ray ray, int i)
{
	t_point		ray_delta;
	t_point		sprite_delta;
	t_point		intersect;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sprite_delta = line_delta(sprite->lines[i].start, sprite->lines[i].end);
	intersect = line_intersection(ray.line.start, ray_delta,\
	sprite->lines[i].start, sprite_delta);
	if (!isnan(intersect.x) && !isnan(intersect.y))
	{
		sprite->visible = sprite->textures[i];
	}
}

void		check_visibility_sprite(t_doom *doom, t_ray ray, int sprite_i,\
			int prev_sector)
{
	t_sprite	*sprite;
	int			i;

	sprite = &doom->lib.sprites[sprite_i];
	i = 0;
	while (i < 4 && sprite->visible == -1)
	{
		detect_sprite(doom, sprite, ray, i);
		i++;
	}
	if (sprite->visible >= 0)
	{
		find_face_sprite(doom, sprite, ray, 0);
		doom->visible_sprites++;
		sprite->sprite_x = ray.plane_x;
		sprite->distance = fabs(point_distance(doom->pos, sprite->pos));
	}
}

static int	scissor_lift_check(t_doom *doom, t_sprite *sprite)
{
	if (doom->own_event.scissor_lift == TRUE && sprite->action == 7)
	{
		sprite->distance = point_distance(doom->pos, sprite->pos);
		return (1);
	}
	else
		return (-1);
}

void		sprite_check(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	int		i;
	int		sprite_i;

	i = 0;
	sprite_i = doom->lib.sector[sector].i_objects;
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprites[sprite_i].visible == -1 &&\
		doom->lib.sprites[sprite_i].action != 6 &&\
		doom->lib.sprites[sprite_i].action != 8 &&\
		doom->lib.sprites[sprite_i].action != 15 &&\
		scissor_lift_check(doom, &doom->lib.sprites[sprite_i]) == -1)
			check_visibility_sprite(doom, ray, sprite_i, prev_sector);
		i++;
		sprite_i++;
	}
}
