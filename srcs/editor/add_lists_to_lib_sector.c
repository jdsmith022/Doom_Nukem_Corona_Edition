#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		set_sector_values(t_doom *doom, t_sector *sector,
					t_ed_sector *ed_sector)
{
	sector->id = ed_sector->id;
	sector->n_sidedefs = ed_sector->n_sidedefs;
	sector->i_sidedefs = ed_sector->i_sidedefs;
	sector->height_floor = ed_sector->height_floor;
	sector->height_ceiling = ed_sector->height_ceiling;
	sector->n_objects = doom->game_design.n_sprites;
	sector->i_objects = doom->game_design.i_sprites;
	sector->light_level = doom->game_design.light_level;
	sector->action = 0;
	sector->hold_light = 0;
	sector->slope_floor_id = -1;
	sector->slope_floor = 0;
	sector->slope_ceiling_id = -1;
	sector->slope_ceiling = 0;
	sector->txt_ceiling = 14;
	sector->txt_floor = 17;
}

void			set_sector_lib(t_doom *doom)
{
	t_ed_sector *ed_sector;
	t_lib		lib;
	int			index;

	ed_sector = doom->game_design.sc_head->next;
	lib.sector = \
		(t_sector*)ft_memalloc(sizeof(t_sector) * doom->game_design.sc_len);
	if (lib.sector == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	index = 0;
	while (ed_sector)
	{
		set_sector_values(doom, &lib.sector[index], ed_sector);
		ft_bzero(ed_sector->previous, sizeof(t_ed_sector));
		free(ed_sector->previous);
		if (ed_sector->next == NULL)
		{
			ft_bzero(ed_sector, sizeof(t_ed_sector));
			free(ed_sector);
		}
		ed_sector = ed_sector->next;
		index++;
	}
}
