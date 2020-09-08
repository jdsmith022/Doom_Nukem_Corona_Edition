/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basket.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:27:54 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static t_item	init_item(t_doom *doom, uint8_t type)
{
	t_item		item;

	item.type = type;
	item.amount = 1;
	set_sprite(doom, type, &item);
	if (!item.sprite)
		ft_putstr("Sprite not found\n");
	doom->own_event.groc_pickup = TRUE;
	return (item);
}

static bool		valid_input(uint8_t type, t_list **head)
{
	if (!type || type > GROC_TYPES)
		return (false);
	return (true);
}

static void		create_next_item(t_doom *doom, t_list *temp, t_item item)
{
	temp->next = ft_lstnew(&item, sizeof(t_item));
	if (temp->next == NULL)
		doom_exit_failure(doom, "error: creating shopping list");
}

void			add_item_to_basket(t_doom *doom, t_list **head, uint8_t type)
{
	t_list		*temp;
	t_item		item;

	temp = *head;
	if (!valid_input(type, head))
		return ;
	item = init_item(doom, type);
	if (!*head)
	{
		*head = ft_lstnew(&item, sizeof(t_item));
		if (head == NULL)
			doom_exit_failure(doom, "error: creating shopping list");
		return ;
	}
	while (!is_in_basket((t_item *)temp->content, type))
	{
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	if (is_in_basket((t_item *)temp->content, type))
		change_amount((t_item *)temp->content, 1);
	else if (get_basket_len(head) < MAX_BASKET_LEN)
		create_next_item(doom, temp, item);
}

bool			remove_item_from_basket(t_list **head, uint8_t type)
{
	t_list		*temp;
	t_item		*item;

	temp = *head;
	if (!temp)
		return (false);
	item = (t_item *)temp->content;
	while (item->type != type)
	{
		if (!temp->next)
			return (false);
		temp = temp->next;
		item = (t_item *)temp->content;
	}
	change_amount(item, -1);
	if (item->amount == 0)
		del_node(head, temp);
	return (true);
}
