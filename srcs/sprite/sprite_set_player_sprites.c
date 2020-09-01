/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_set_player_sprites.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 09:44:46 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/01 11:11:14 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

static void	set_player_sprite_3(t_doom *doom)
{
	if (doom->player.handed == right)
	{
		doom->player.spray_hand = 106;
		doom->player.spraying_hand = 111;
	}
	else
	{
		doom->player.spray_hand = 29;
		doom->player.spraying_hand = 30;
	}
	doom->player.left_select = 74;
	doom->player.right_select = 75;
}

static void	set_player_sprite_2(t_doom *doom)
{
	if (doom->player.handed == right)
	{
		doom->player.spray_hand = 104;
		doom->player.spraying_hand = 110;
	}
	else
	{
		doom->player.spray_hand = 105;
		doom->player.spraying_hand = 109;
	}
	doom->player.left_select = 100;
	doom->player.right_select = 101;
}

void		set_player_sprite(t_doom *doom)
{
	if (doom->player.character == player_1)
	{
		if (doom->player.handed == right)
		{
			doom->player.spray_hand = 102;
			doom->player.spraying_hand = 108;
		}
		else
		{
			doom->player.spray_hand = 103;
			doom->player.spraying_hand = 107;
		}
		doom->player.left_select = 98;
		doom->player.right_select = 99;
	}
	else if (doom->player.character == player_2)
		set_player_sprite_2(doom);
	else if (doom->player.character == player_3)
		set_player_sprite_3(doom);
	doom->player.character = set;
}
