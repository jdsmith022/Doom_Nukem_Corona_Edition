/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:28:50 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

bool		is_in_basket(t_item *item, uint8_t type)
{
	if (item->type == type)
		return (true);
	return (false);
}

bool		search_basket(t_item *itema, t_list **head)
{
	t_list		*temp;
	t_item		*itemb;

	temp = *head;
	if (!temp)
		return (false);
	while (temp)
	{
		itemb = (t_item *)temp->content;
		if (itema->type == itemb->type && itema->amount == itemb->amount)
			return (true);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (false);
}

t_item		*get_item_from_basket(uint8_t type, t_list **head)
{
	t_list		*temp;
	t_item		*item;

	temp = *head;
	if (!temp)
		return (NULL);
	while (temp)
	{
		item = (t_item *)temp->content;
		if (item->type == type)
			return (item);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (NULL);
}

bool		change_amount(t_item *item, int8_t amount)
{
	if (amount + item->amount > 10)
		return (false);
	else if (amount + item->amount < 0)
		return (false);
	item->amount += amount;
	return (true);
}
