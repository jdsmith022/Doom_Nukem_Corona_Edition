/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_collision.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:33 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/07 11:39:31 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

static int	sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	int		value;

	value = 0;
	if (sprite.action == 13)
	{
		get_game_over_info(doom);
		doom->menu->state = finished;
		return (-1);
	}
	if ((sprite.action == 7 && doom->own_event.scissor_lift == FALSE)\
	|| sprite.action == 9 || sprite.action == 12)
		value = 15;
	if (movement.end.x >= sprite.lines[0].start.x - value &&\
	movement.end.x <= sprite.lines[0].end.x + value &&\
	movement.end.y >= sprite.lines[1].start.y - value &&\
	movement.end.y <= sprite.lines[1].end.y + value)
		return (1);
	return (-1);
}

void		exit_scissor_lift(t_doom *doom)
{
	double		distance;

	distance = point_distance(doom->pos,\
	doom->lib.sprites[doom->save_scissor_lift].pos);
	if (distance > 60)
	{
		doom->save_scissor_lift = -1;
		doom->own_event.scissor_lift = FALSE;
		doom->own_event.scissor_lift_down = FALSE;
	}
	else
	{
		doom->own_event.parked_too_close = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
	}
}

static void	activate_scissor_lift(t_doom *doom, int index)
{
	doom->own_event.scissor_lift = TRUE;
	doom->lib.font_lib.bools.text = TRUE;
	doom->lib.font_lib.bools.scissor_lift = TRUE;
	doom->pos.x = doom->lib.sprites[index].pos.x;
	doom->pos.y = doom->lib.sprites[index].pos.y;
	doom->save_scissor_lift = index;
	doom->player.height += 10;
}

int			sprite_collision(t_doom *doom, t_line movement)
{
	int		x;
	int		sector;
	int		index;

	x = 0;
	sector = doom->i_sector;
	index = doom->lib.sector[sector].i_objects;
	while (x < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprites[index].block == 1)
		{
			if (doom->lib.sprites[index].distance < 70\
			&& doom->own_event.scissor_lift == FALSE &&\
			doom->lib.sprites[index].action == 7)
				activate_scissor_lift(doom, index);
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		check_sprite_distance(doom, index);
		index++;
		x++;
	}
	return (-1);
}
