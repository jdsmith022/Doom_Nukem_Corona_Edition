/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_menu.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 12:47:13 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"
#include "../../includes/render.h"

static void		print_missing_groceries(t_doom *doom)
{
	char		*score;
	t_item		*info;
	size_t		index;

	index = 0;
	info = doom->groceries->info.groceries_to_display;
	info->position.y = HEIGHT - 200;
	info->position.x = WIDTH / doom->groceries->shopping_list_len - 25;
	while (index < doom->groceries->shopping_list_len)
	{
		info->position.x += 100;
		if (info[index].amount != 0)
		{
			draw_img(info[index].sprite, doom, info->position);
			draw_grocery_amount(doom, \
				info->position, ft_itoa(info[index].amount));
		}
		index++;
	}
}

void			menu_print_loop(t_doom *doom)
{
	mouse_settings(doom);
	print_background(doom, 0x00002E);
	if (doom->groceries)
	{
		if (doom->groceries->info.won == FALSE && \
		doom->menu->state == finished)
			print_missing_groceries(doom);
	}
	font_to_screen(doom);
	set_to_window(doom);
}
