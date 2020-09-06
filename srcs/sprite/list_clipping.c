/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_clipping.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 10:59:34 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/06 20:02:38 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void		free_clipping_values(t_doom *doom, t_clip *list)
{
	t_clip		*node;
	t_clip		*temp;

	//free bottom
	node = list->next;
	//standard free function for t_clip linked list
	if (node == NULL)
	{
		// printf("return\n");
		return ;
	}
	while (node->next != NULL)
	{
		temp = node->next;
		printf("free #%d S#%d (%f;%f)-(%f;%f)\n", node->id, node->sidedef, node->line.start.x, node->line.start.y, node->line.end.x, node->line.end.y);
		ft_bzero(node, sizeof(t_clip));
		free(node);
		node = temp;
	}
	list->next = NULL;
}

t_clip		*new_clip_start(int id, int x, int y, int sidedef)
{
	t_clip	*new;

	new = (t_clip*)malloc(sizeof(t_clip));
	if (!new)
		return (NULL);
	// if (id == NULL || x == NULL || y == NULL)
	// {
	// 	new->id = 0;
	// 	new->line.start.x = -1;
	// 	new->line.start.y = -1;
	// 	new->line.end.x = -1;
	// 	new->line.end.y = -1;
	// }
	else
	{
		new->id = id;
		new->line.start.x = x;
		new->line.start.y = y;
		new->sidedef = sidedef;
	}
	new->next = NULL;
	return (new);
}
