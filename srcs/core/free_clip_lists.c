/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_clip_lists.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 11:16:31 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/09/07 11:26:53 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void	delete_clip_list(t_doom *doom, t_clip *list)
{
	free_clipping_values(doom, list);
	ft_bzero(list, sizeof(t_clip));
	free(list);
}

void		free_clip_lists(t_doom *doom)
{
	if (doom->clip->bottom)
		delete_clip_list(doom, doom->clip->head_bottom);
	if (doom->clip->mid_bottom)
		delete_clip_list(doom, doom->clip->head_mid_bottom);
	if (doom->clip->top)
		delete_clip_list(doom, doom->clip->head_top);
	free(doom->clip);
}