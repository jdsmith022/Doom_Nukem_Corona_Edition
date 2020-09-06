/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_clipping.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 10:59:34 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/06 21:59:10 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void		free_clipping_values(t_doom *doom, t_clip *list)
{
	t_clip		*node;
	t_clip		*temp;

	node = list->next;
	if (node == NULL)
		return ;
	while (node->next != NULL)
	{
		temp = node->next;
		// printf("free #%d S#%d (%f;%f)-(%f;%f)\n", node->id, node->sidedef, node->line.start.x, node->line.start.y, node->line.end.x, node->line.end.y);
		ft_bzero(node, sizeof(t_clip));
		free(node);
		node = temp;
	}
	list->next = NULL;
}

t_clip		*new_clip_start(int sector_id, int x, int y, int sidedef)
{
	t_clip	*new;

	new = (t_clip*)malloc(sizeof(t_clip));
	if (!new)
		return (NULL);
	else
	{
		new->sector_id = sector_id;
		new->line.start.x = x;
		new->line.start.y = y;
		new->sidedef = sidedef;
	}
	new->next = NULL;
	return (new);
}
