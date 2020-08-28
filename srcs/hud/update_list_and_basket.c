/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_list_and_basket.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:17:37 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:17:38 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
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
	}
}
