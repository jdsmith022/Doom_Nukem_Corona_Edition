#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static void	set_sidedef_values(t_doom *doom, t_sidedef *sidedef,
				t_ed_sidedef *ed_sidedef)
{
	sidedef->id = ed_sidedef->id;
	sidedef->line = ed_sidedef->line;
	sidedef->txt_1 = 14;
	sidedef->txt_2 = ed_sidedef->texture;
	sidedef->txt_3 = 17;
	sidedef->sector = ed_sidedef->sector;
	sidedef->opp_sector = ed_sidedef->opp_sector;
	sidedef->action = 0;
	sidedef->poster = -1;
}

void		set_sidedef_lib(t_doom *doom)
{
	t_ed_sidedef	*ed_sidedef;
	t_lib			lib;
	int				index;
	t_item			groceries[doom->game_design.sd_len];

	ed_sidedef = doom->game_design.sd_head->next;
	lib.sidedef = \
		(t_sidedef*)ft_memalloc(sizeof(t_sidedef) * doom->game_design.sd_len);
	if (lib.sidedef == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	index = 0;
	while (ed_sidedef)
	{
		set_sidedef_values(doom, &lib.sidedef[index], ed_sidedef);
		groceries[index].type = \
			(uint8_t)doom->lib.tex_lib[ed_sidedef->texture]->userdata;
		ft_bzero(ed_sidedef->previous, sizeof(t_ed_sidedef));
		free(ed_sidedef->previous);
		if (ed_sidedef->next == NULL)
		{
			ft_bzero(ed_sidedef, sizeof(t_ed_sidedef));
			free(ed_sidedef);
		}
		ed_sidedef = ed_sidedef->next;
		index++;
	}
	index = 0;
	doom->groceries->groceries_in_level = groceries;
	doom->lib.sidedef = lib.sidedef;
}
