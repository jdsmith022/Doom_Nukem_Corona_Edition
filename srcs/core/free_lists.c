/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_lists.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 09:13:50 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 22:32:25 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void	delete_sprite_list(t_doom *doom, t_ed_sprite *ed_sprite)
{
	ed_sprite = ed_sprite->next;
	while (ed_sprite)
	{
		ft_bzero(ed_sprite->previous, sizeof(t_ed_sprite));
		free(ed_sprite->previous);
		if (ed_sprite->next == NULL)
		{
			ft_bzero(ed_sprite, sizeof(t_ed_sprite));
			free(ed_sprite);
		}
		ed_sprite = ed_sprite->next;
	}
}

void		free_lists(t_doom *doom)
{
	if (doom->game_design.sp_head)
		delete_sprite_list(doom, doom->game_design.sp_head);
}
