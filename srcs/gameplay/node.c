/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 23:43:42 by elkanfrank    ########   odam.nl         */
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
		printf("Freed first node\n");
		if (node->next)
			*head = node->next;
		else {
			*head = NULL;
			printf("List empty: head pointed to null\n");
		}
		free(node);
		return ;
	}
	while (prev->next->content != node->content)
		prev = prev->next;
	if (node->next)
		prev = node->next;
	else {
		printf("Deleted last node; pointed to null\n");
		prev->next = NULL;
	}
	printf("Freed non-first node\n");
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
