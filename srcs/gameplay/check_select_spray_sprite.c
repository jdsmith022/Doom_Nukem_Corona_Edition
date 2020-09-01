/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_select_spray_sprite.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:20:00 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/01 15:14:41 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"
#include "../../includes/sprites.h"

static void	check_select_sprite2(t_doom *doom, t_sprite *sprite)
{
	uint8_t		type;

	if (sprite->action == 4)
		doom->hud->update = corona_hit;
	else if (sprite->action == 11)
	{
		doom->game.start_time.tv_sec += 60;
		sprite->action = 8;
	}
	else if (sprite->action == 12)
	{
		doom->own_event.trolly = TRUE;
		doom->lib.sidedef[17].action = 0;
		sprite->action = 15;
	}
	else if (sprite->action == 14)
	{
		type = *(int *)doom->lib.obj_lib[sprite->textures[0]]->userdata;
		sprite->action = 15;
		if (!doom->groceries)
			return ;
		add_item_to_basket(doom, &doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
}

static void	check_select_sprite(t_doom *doom)
{
	t_sprite	*sprite;

	sprite = &doom->lib.sprites[doom->own_event.hit_index];
	if (sprite->action == 1)
	{
		doom->hud->update = health_pack_plus;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.health_pack = TRUE;
	}
	else if (sprite->action == 2)
	{
		doom->hud->update = health_pack;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.health_pack = TRUE;
	}
	else if (sprite->action == 3)
	{
		doom->hud->update = facemask;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.facemask = TRUE;
	}
	if (sprite->action == 1 || sprite->action == 2 || sprite->action == 3)
		sprite->action = 8;
	else
		check_select_sprite2(doom, sprite);
}

static void	virus_hit(t_doom *doom)
{
	doom->lib.sprites[doom->own_event.hit_index].visible = 17;
	doom->lib.sprites[doom->own_event.hit_index].textures[0] = 17;
	doom->lib.sprites[doom->own_event.hit_index].textures[1] = 17;
	doom->lib.sprites[doom->own_event.hit_index].textures[2] = 17;
	doom->lib.sprites[doom->own_event.hit_index].textures[3] = 17;
	doom->lib.sprites[doom->own_event.hit_index].action = 5;
	doom->own_event.virus_red_i = doom->own_event.hit_index;
	doom->own_event.virus_red = TRUE;
}

static void	check_spray_sprite(t_doom *doom)
{
	int		index;

	index = doom->own_event.hit_index;
	if (doom->lib.sprites[index].action == 4)
		virus_hit(doom);
	else if (doom->lib.sprites[index].action == 9 && \
	doom->lib.sprites[index].distance < 100.0)
	{
		doom->own_event.spray_shopper = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
	}
}

void		check_select_spray_sprite(t_doom *doom)
{
	if (doom->lib.sprites[doom->own_event.hit_index].distance < 100.0)
	{
		if (doom->own_event.shoot == TRUE)
			check_spray_sprite(doom);
		else if (doom->own_event.select == TRUE)
			check_select_sprite(doom);
	}
	doom->own_event.hit_index = -1;
}
