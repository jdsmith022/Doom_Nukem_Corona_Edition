#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

int		sprite_in_shooting_area(t_doom *doom, int sprite_i)
{
	// printf("begin sprite in shooting area\n");
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

bool	sprite_has_action(t_sprite sprite)
{
	int action;

	// printf("begin sprite_has_action\n");
	action = sprite.action;
	if (action == 4 || action == 9 || action == 13 ||
	action == 11 || action == 12 || action == 14)
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
