#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		delete_portals(t_doom *doom, int sector)
{
	t_ed_sidedef *sidedef;

	sidedef = doom->game_design.sd_head;
	while (sidedef->next != NULL)
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
	ft_bzero(editor->ed_sidedef, sizeof(t_ed_sidedef));
	editor->ed_sidedef->next = NULL;
	editor->ed_sidedef->id = 0;
	editor->sd_head = editor->ed_sidedef;
	ft_bzero(editor->ed_sector, sizeof(t_ed_sector));
	editor->draw_line.start.x = -1;
	editor->draw_line.start.y = -1;
	editor->draw_line.end.x = -1;
	editor->draw_line.end.y = -1;
	editor->ed_sector->next = NULL;
	doom->game_design.ed_sector->light_level = 10;
	doom->game_design.ed_sector->height_ceiling = 0;
	doom->game_design.ed_sector->height_floor = 0;
	doom->game_design.ed_sector->id = 0;
	if (doom->game_design.sd_len == 1)
		doom->game_design.sd_len = 0;
	editor->edit_sector = FALSE;
}

static void		delete_sidedefs_in_sector(t_doom *doom, int sector)
{
	t_ed_sidedef	*sidedef;
	t_ed_sidedef	*previous;
	t_ed_sidedef	*next;

	sidedef = doom->game_design.sd_head;
	while (sidedef->next != NULL && sidedef->sector != sector)
		sidedef = sidedef->next;
	while (sidedef && sidedef->sector == sector && doom->game_design.sd_len > 1)
	{
		previous = sidedef->previous;
		next = sidedef->next;
		if (previous != NULL)
			previous->next = next;
		if (next != NULL)
			next->previous = previous;
		ft_bzero(sidedef, sizeof(t_ed_sidedef));
		free(sidedef);
		if (next == NULL)
			sidedef = previous;
		else
			sidedef = next;
		doom->game_design.sd_len--;
	}
	doom->game_design.ed_sidedef = sidedef;
	doom->game_design.cur_sd = sidedef->id;
}

void			delete_sector(t_doom *doom)
{
	int				sector;

	sector = doom->game_design.ed_sidedef->sector;
	delete_sidedefs_in_sector(doom, sector);
	delete_sprites_in_sector(doom, sector);
	doom->game_design.sc_len--;
	if (doom->game_design.sd_len == 1)
		reset_values(doom);
	else
		delete_portals(doom, sector);
}
