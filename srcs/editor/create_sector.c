#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		set_sector_sidedefs(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	int				i_sidedef;
	int				n_sidedefs;

	i_sidedef = -1;
	n_sidedefs = 0;
	sidedef = doom->game_design.sd_head;
	while (sidedef->next != NULL)
	{
		sidedef = sidedef->next;
		if (i_sidedef == -1 && sidedef->sector == doom->game_design.sc_len)
			i_sidedef = sidedef->id;
		if (sidedef->sector == doom->game_design.sc_len)
			n_sidedefs++;
	}
	doom->game_design.ed_sector->i_sidedefs = i_sidedef;
	doom->game_design.ed_sector->n_sidedefs = n_sidedefs;
}

void			set_ed_sector_values(t_doom *doom)
{
	t_ed_sector *prev;
	int			id;

	id = doom->game_design.sc_len;
	while (doom->game_design.ed_sector->next != NULL)
		doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->next = ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector->next)
		doom_exit_failure(doom, "error: malloc sector in editor\n");
	prev = doom->game_design.ed_sector;
	doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->previous = prev;
	set_sector_sidedefs(doom);
	doom->game_design.ed_sector->height_floor = doom->game_design.floor_height;
	doom->game_design.ed_sector->height_ceiling =\
		doom->game_design.ceiling_height;
	doom->game_design.ed_sector->light_level = doom->game_design.light_level;
	doom->game_design.ed_sector->id = id;
	doom->game_design.ed_sector->next = NULL;
	doom->game_design.open_connection = TRUE;
	doom->game_design.sc_len++;
}
