#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

static void	delete_list(t_doom *doom)
{
	t_ed_sprite *ed_sprite;

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

void		set_sprite_lib(t_doom *doom)
{
	t_ed_sprite *ed_sprite;
	t_lib		lib;
	int			index;
	int			sc_index;
	int			spr_index;

	ed_sprite = doom->game_design.sp_head->next;
	lib.sprites = \
		(t_sprite*)ft_memalloc(sizeof(t_sprite) * doom->game_design.spr_len);
	if (lib.sprites == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	index = 0;
	sc_index = 0;
	spr_index = -1;
	while (sc_index < doom->game_design.sc_len && ed_sprite)
	{
		if (ed_sprite->sector == sc_index)
		{
			if (spr_index == -1)
				spr_index = index;
			set_sprite_values(doom, &lib.sprites[index], ed_sprite);
			index++;
		}
		ed_sprite = ed_sprite->next;
		if (ed_sprite == NULL && sc_index < doom->game_design.sc_len)
		{
			doom->lib.sector[sc_index].i_objects = spr_index;
			doom->lib.sector[sc_index].n_objects = index - spr_index;
			ed_sprite = doom->game_design.sp_head->next;
			sc_index++;
			spr_index = -1;
		}
	}
	delete_list(doom);
	doom->lib.sprites = lib.sprites;
	doom->total_sprites = doom->game_design.spr_len;
}
