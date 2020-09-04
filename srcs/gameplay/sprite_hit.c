/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_hit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 14:50:49 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/03 17:44:13 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/sprites.h"

static bool		sprite_has_action(t_sprite sprite)
{
	int action;

	action = sprite.action;
	if (action == 1 || action == 2 || action == 3 ||
	action == 4 || action == 9 || action == 13 || action == 11 ||
	action == 12 || action == 14)
		return (true);
	return (false);
}

static int		sprite_in_shooting_area(t_doom *doom, int sprite_i)
{
	if (doom->own_event.hold_x >=
	(int)doom->lib.sprites[sprite_i].sprite_begin.x &&
	doom->own_event.hold_x <= (int)doom->lib.sprites[sprite_i].sprite_begin.x +
	(int)doom->lib.sprites[sprite_i].width &&
	doom->own_event.hold_y >=
	(int)doom->lib.sprites[sprite_i].sprite_begin.y &&
	doom->own_event.hold_y <=
	(int)doom->lib.sprites[sprite_i].sprite_begin.y +
	(int)doom->lib.sprites[sprite_i].height)
		return (sprite_i);
	return (-1);
}

static void		check_hit_new(t_doom *doom)
{
	int			i;

	i = 0;
	while (i < doom->visible_sprites)
	{
		if (doom->lib.sprites[doom->lib.sprite_order[i]].distance < 320 &&
		sprite_has_action(doom->lib.sprites[doom->lib.sprite_order[i]]) &&
		sprite_in_shooting_area(doom, doom->lib.sprite_order[i]) != -1)
			doom->own_event.hit_index = doom->lib.sprite_order[i];
		i++;
	}
}

void			check_sprite_hit(t_doom *doom)
{
	t_ray	ray;

	check_hit_new(doom);
	if (doom->own_event.hit_index != -1)
		check_select_spray_sprite(doom);
	doom->own_event.hit_index = -1;
}
