#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

int		sprite_in_shooting_area(t_doom *doom, int sprite_i)
{
	if (doom->own_event.hold_x >=
	(int)doom->lib.sprites[sprite_i].sprite_begin.x &&
	doom->own_event.hold_x <= (int)doom->lib.sprites[sprite_i].sprite_begin.x +
	(int)SPRITES[sprite_i].width &&
	doom->own_event.hold_y >=
	(int)doom->lib.sprites[sprite_i].sprite_begin.y &&
	doom->own_event.hold_y <=
	(int)doom->lib.sprites[sprite_i].sprite_begin.y +
	(int)doom->lib.sprites[sprite_i].height)
		return (sprite_i);
	return (-1);
}

int		sprite_in_range(t_doom *doom, t_ray ray, int sprite_i,
					int prev_sector)
{
	int			i;
	t_point		ray_delta;
	t_point		sprite_delta;
	t_point		intersect;

	i = 0;
	while (i < 4)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(doom->lib.sprites[sprite_i].lines[i].start,
			doom->lib.sprites[sprite_i].lines[i].end);
		intersect = line_intersection(ray.line.start, ray_delta,
		doom->lib.sprites[sprite_i].lines[i].start, sprite_delta);
		if (isnan(intersect.x) && isnan(intersect.y))
		{
			if (sprite_in_shooting_area(doom, sprite_i) == -1)
				return (-1);
			return (sprite_i);
		}
		i++;
	}
	return (-1);
}

bool	sprite_has_action(t_sprite sprite)
{
	int action;

	action = sprite.action;
	if (action == 4 || action == 9 || action == 13 ||
	action == 11 || action == 12)
		return (true);
	return (false);
}

double	get_sprite_dist(t_doom *doom, int sprite_hit)
{
	if (sprite_hit == -1)
		return (INFINITY);
	else
		return (doom->lib.sprites[sprite_hit].distance);
}
