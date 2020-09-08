/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:28:38 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

void		del_node(t_list **head, t_list *node)
{
	t_list	*prev;

	prev = *head;
	if (prev->content == node->content)
	{
		*head = node->next;
		free(node);
		return ;
	}
	while (prev->next->content != node->content)
		prev = prev->next;
	prev->next = node->next;
	free(node);
}

static void	free_list(t_list *head)
{
	t_list *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);
	}
}

void		del_groceries(t_groceries *groc)
{
	free(groc->shopping_list);
	free_list(groc->basket);
	free(groc);
}
