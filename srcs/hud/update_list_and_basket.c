/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_list_and_basket.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:16:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 18:03:29 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"

void	update_list_and_basket(t_doom *doom)
{
	if (doom->groceries->basket)
		draw_basket_ui(doom, doom->groceries);
	if (doom->groceries->shopping_list)
		draw_shopping_ui(doom, doom->groceries);
	if (doom->lib.sector[doom->i_sector].action == EXIT_LEVEL)
	{
		get_game_over_info(doom);
		doom->menu->state = finished;
		stop_sounds();
		play_sound(doom->audio->sounds[LEVEL_EXIT], 1);
	}
}
