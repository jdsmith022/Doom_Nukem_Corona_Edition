/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_shopping_list.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 19:52:26 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static t_item	new_item(uint8_t type, int i)
{
	t_item		item;

	item.type = type;
	item.amount = (rand() % 5) + 1;
	item.position = get_position(i, WIDTH - 35, 60);
	return (item);
}

static bool		is_duplicate(uint32_t num, t_item *s_list, uint16_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		if (num == s_list[i].type)
			return (true);
		i++;
	}
	return (false);
}

void			custom_shopping_list(t_doom *doom, t_groceries *groceries)
{
	uint32_t	random_index;
	t_item		*groc_in_lvl;
	t_item		*s_list;
	uint8_t		i;

	s_list = groceries->shopping_list;
	groc_in_lvl = doom->groceries->groceries_in_level;
	i = 0;
	srand(time(0));
	random_index = rand() % (doom->groceries->num_of_groceries);
	while (i < groceries->shopping_list_len)
	{
		while (is_duplicate(groc_in_lvl[random_index].type, s_list, i))
			random_index = rand() % (doom->groceries->num_of_groceries);
		s_list[i] = new_item(groc_in_lvl[random_index].type, i);
		set_sprite(doom, s_list[i].type, &s_list[i]);
		i++;
	}
	free(groceries->groceries_in_level);
}
