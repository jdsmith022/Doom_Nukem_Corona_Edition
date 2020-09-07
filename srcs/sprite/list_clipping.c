/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_clipping.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 10:59:34 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/07 12:47:25 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void		init_clipping(t_doom *doom)
{
	doom->clip = (t_clip_lists*)ft_memalloc(sizeof(t_clip_lists));
	if (!doom->clip)
		doom_exit_failure(doom, "error: failed malloc\n");
	doom->clip->bottom = (t_clip*)ft_memalloc(sizeof(t_clip));
	if (!doom->clip->bottom)
		doom_exit_failure(doom, "error: failed malloc\n");
	doom->clip->bottom->next = NULL;
	doom->clip->head_bottom = doom->clip->bottom;
	doom->clip->top = (t_clip*)ft_memalloc(sizeof(t_clip));
	if (!doom->clip->top)
		doom_exit_failure(doom, "error: failed malloc\n");
	doom->clip->top->next = NULL;
	doom->clip->head_top = doom->clip->top;
	doom->clip->mid_bottom = (t_clip*)ft_memalloc(sizeof(t_clip));
	if (!doom->clip->mid_bottom)
		doom_exit_failure(doom, "error: failed malloc\n");
	doom->clip->mid_bottom->next = NULL;
	doom->clip->head_mid_bottom = doom->clip->mid_bottom;
}

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
		new->line.end.x = WIDTH;
		new->line.end.y = 0;
		new->sidedef = sidedef;
	}
	new->next = NULL;
	return (new);
}
