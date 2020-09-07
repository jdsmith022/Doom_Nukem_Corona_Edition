/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_lists.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 09:13:50 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 18:17:43 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void	delete_sector_list(t_doom *doom, t_ed_sector *ed_sector)
{
	ed_sector = doom->game_design.sc_head->next;
	while (ed_sector)
	{
		ft_bzero(ed_sector->previous, sizeof(t_ed_sector));
		free(ed_sector->previous);
		if (ed_sector->next == NULL)
		{
			ft_bzero(ed_sector, sizeof(t_ed_sector));
			free(ed_sector);
		}
		ed_sector = ed_sector->next;
	}
}

static void	delete_sidedef_list(t_doom *doom, t_ed_sidedef *ed_sidedef)
{
	ed_sidedef = doom->game_design.sd_head->next;
	while (ed_sidedef)
	{
		ft_bzero(ed_sidedef->previous, sizeof(t_ed_sidedef));
		free(ed_sidedef->previous);
		if (ed_sidedef->next == NULL)
		{
			ft_bzero(ed_sidedef, sizeof(t_ed_sidedef));
			free(ed_sidedef);
		}
		ed_sidedef = ed_sidedef->next;
	}
}

static void	delete_sprite_list(t_doom *doom, t_ed_sprite *ed_sprite)
{
	ed_sprite = doom->game_design.sp_head->next;
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
	if (doom->game_design.ed_sprite)
		delete_sprite_list(doom, doom->game_design.ed_sprite);
	if (doom->game_design.ed_sector)
		delete_sector_list(doom, doom->game_design.ed_sector);
	if (doom->game_design.ed_sidedef)
		delete_sidedef_list(doom, doom->game_design.ed_sidedef);
}
