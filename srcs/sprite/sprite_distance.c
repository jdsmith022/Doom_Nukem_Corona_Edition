/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_distance.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:02:29 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/07 22:37:18 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

static void	check_walking(t_doom *doom, t_sprite shopper)
{
	double new_dist;

	if (doom->own_event.sprite_collision == FALSE)
	{
		doom->own_event.sprite_collision_dist = shopper.distance;
		doom->own_event.sprite_collision = TRUE;
		doom->hud->update = shopper_collision;
		doom->own_event.sprite_index = shopper.index;
	}
	else if (shopper.distance > doom->own_event.sprite_collision_dist\
	&& doom->own_event.sprite_collision == TRUE &&\
	doom->own_event.sprite_index == shopper.index)
	{
		doom->own_event.sprite_collision = FALSE;
		doom->own_event.sprite_collision_dist = -1;
		doom->own_event.sprite_index = -1;
	}
}

static void	check_checkout_action(t_doom *doom, int index)
{
	if (doom->lib.sprites[index].action == 13)
	{
		get_game_over_info(doom);
		doom->menu->state = finished;
	}
}

static void	check_sprite_distance2(t_doom *doom, int index)
{
	if (doom->lib.sprites[index].action == 2)
	{
		doom->hud->update = health_pack;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.health_pack = TRUE;
		doom->lib.sprites[index].action = 8;
	}
	else if (doom->lib.sprites[index].action == 3)
	{
		doom->hud->update = facemask;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.facemask = TRUE;
		doom->lib.sprites[index].action = 8;
	}
	else if (doom->lib.sprites[index].action == 10)
	{
		if (doom->own_event.scissor_lift == FALSE)
		{
			doom->lib.sprites[index].action = 8;
			doom->own_event.fall = TRUE;
		}
	}
	check_checkout_action(doom, index);
}

void		check_sprite_distance(t_doom *doom, int index)
{
	if (doom->lib.sprites[index].distance > 0.1 &&\
	doom->lib.sprites[index].distance < 50)
	{
		if (doom->lib.sprites[index].action == 9)
			check_walking(doom, doom->lib.sprites[index]);
		else if (doom->lib.sprites[index].action == 4)
		{
			doom->hud->update = corona_hit;
			doom->lib.sprites[index].action = 6;
		}
		else if (doom->lib.sprites[index].action == 1)
		{
			doom->hud->update = health_pack_plus;
			doom->lib.font_lib.bools.text = TRUE;
			doom->lib.font_lib.bools.health_pack = TRUE;
			doom->lib.sprites[index].action = 8;
		}
		else if (doom->lib.sprites[index].action == 11)
		{
			doom->game.start_time.tv_sec += 60;
			doom->lib.sprites[index].action = 8;
		}
		else
			check_sprite_distance2(doom, index);
	}
}
