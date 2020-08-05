#include "../../includes/doom.h"

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
			sprite->distance = fabs(points_distance(doom->pos, sprite->pos));
		}
		i++;
	}
}

/*
**		do i need to loop through all sides? Once I've detected one sidedef,
**		it can stop.
**		if there are more faces, I need to loop through faces
*/

void		check_visibility_sprite(t_doom *doom, t_sprite *sprite, t_ray ray, int i, int sprite_i, int prev_sector)
{
	t_point		ray_delta;
	t_point		sprite_delta;
	t_point		intersect;
	double		curr_distance;
	double		temp_distance;
	// t_sprite	sprite;

	temp_distance = INFINITY;
	curr_distance = 0;
	while (i < 4)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(sprite->lines[i].start, sprite->lines[i].end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		sprite->lines[i].start, sprite_delta);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			curr_distance = point_distance(doom->pos, intersect, ray.angle);
			if (curr_distance < temp_distance)
			{
				temp_distance = curr_distance;
				sprite->visible = sprite->textures[i];
			}
			// sprite->distance = fabs(point_distance(doom->pos, intersect, ray.angle)); //this is not the real distance
			sprite->distance = fabs(points_distance(doom->pos, sprite->pos));
		}
		i++;
	}
	if (sprite->visible != -1)
	{
		find_face_sprite(doom, sprite, ray, 0);
		doom->visible_sprites++;
		sprite->sprite_x = ray.plane_x;
	}
}

void		sprite_check(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	int		i;
	int		x;
	int		sprite_i;

	i = 0;
	x = 0;
	sprite_i = doom->lib.sector[sector].i_objects; //dit moet ik checken
	doom->lib.sprites[sprite_i].angle = ray.angle;
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprites[sprite_i].visible == -1)
			check_visibility_sprite(doom, &doom->lib.sprites[sprite_i], ray, x, sprite_i, prev_sector);
		i++;
		sprite_i++;
	}
}
