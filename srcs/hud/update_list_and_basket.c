/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_list_and_basket.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:16:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 20:16:14 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"

void	update_list_and_basket(t_doom *doom)
{
	if (!doom->groceries)
		return ;
	if (doom->groceries->basket)
		draw_basket_ui(doom, doom->groceries);
	if (doom->groceries->shopping_list)
		draw_shopping_ui(doom, doom->groceries);
}
