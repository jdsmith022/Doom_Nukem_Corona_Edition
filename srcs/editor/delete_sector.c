/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_sector.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 21:26:21 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		free_sectors(t_doom *doom, int del_sector)
{
	t_ed_sector	*sector;
	t_ed_sector	*del;
	t_ed_sector	*next;

	sector = doom->game_design.sc_head;
	while (sector != NULL && sector->next->id < del_sector)
		sector = sector->next;
	doom->game_design.ed_sector = sector;
	del = sector->next;
	sector->next = NULL;
	while (del)
	{
		doom->game_design.sc_len--;
		next = del->next;
		ft_bzero(del, sizeof(t_ed_sector));
		free(del);
		del = next;
	}
}

static void		delete_portals(t_doom *doom, int sector)
{
	t_ed_sidedef *sidedef;

	sidedef = doom->game_design.sd_head->next;
	while (sidedef != NULL)
	{
		if (sidedef->opp_sector == sector)
			sidedef->opp_sector = -1;
		sidedef = sidedef->next;
	}
}

static void		reset_values(t_doom *doom)
{
	t_gamedesign *editor;

	editor = &doom->game_design;
	doom->game_design.ed_sidedef->id = 0;
	doom->game_design.ed_sector->id = 0;
	doom->game_design.sd_head = doom->game_design.ed_sidedef;
	doom->game_design.draw_line.start.x = -1;
	doom->game_design.draw_line.start.y = -1;
	doom->game_design.draw_line.end.x = -1;
	doom->game_design.draw_line.end.y = -1;
	doom->game_design.ed_sector->light_level = 10;
	doom->game_design.ed_sector->height_ceiling = 0;
	doom->game_design.ed_sector->height_floor = 0;
	doom->game_design.ed_sector->id = 0;
	if (doom->game_design.sc_len > 0)
		doom->game_design.open_connection = TRUE;
	else
		doom->game_design.open_connection = FALSE;
	doom->game_design.edit_sector = FALSE;
}

static void		delete_sidedefs_in_sector(t_doom *doom, int sector)
{
	t_ed_sidedef	*sidedef;
	t_ed_sidedef	*del;
	t_ed_sidedef	*next;

	sidedef = doom->game_design.sd_head;
	while (sidedef != NULL && sidedef->next->sector < sector)
	{
		sidedef = sidedef->next;
		if (sidedef->opp_sector == sector)
			sidedef->opp_sector = -1;
	}
	doom->game_design.ed_sidedef = sidedef;
	del = sidedef->next;
	sidedef->next = NULL;
	while (del)
	{
		doom->game_design.sd_len--;
		next = del->next;
		ft_bzero(del, sizeof(t_ed_sidedef));
		free(del);
		del = next;
	}
}

void			delete_sector(t_doom *doom)
{
	int				sector;

	sector = doom->game_design.ed_sidedef->sector;
	delete_portals(doom, sector);
	delete_sidedefs_in_sector(doom, sector);
	free_sectors(doom, sector);
	if (doom->game_design.spr_len > 0)
		delete_sprites_in_sector(doom, sector);
	if (doom->game_design.sc_len == 0)
		reset_values(doom);
}
