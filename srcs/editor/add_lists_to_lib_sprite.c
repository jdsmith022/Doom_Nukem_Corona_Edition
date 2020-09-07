/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_lists_to_lib_sprite.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 17:32:03 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

static void		delete_list(t_doom *doom)
{
	t_ed_sprite *ed_sprite;
	t_ed_sprite *next;

	ed_sprite = doom->game_design.sp_head->next;
	while (ed_sprite)
	{
		next = ed_sprite->next;
		ft_bzero(ed_sprite, sizeof(t_ed_sprite));
		free(ed_sprite);
		ed_sprite = next;
	}
}

static void		set_sector_sprite_values(t_sector *sector, int *spr_index,\
				int *sc_index, int index)
{
	sector->i_objects = *spr_index;
	sector->n_objects = index - *spr_index;
	*spr_index = -1;
}

static void		sort_sprite_per_sector(t_doom *doom, t_lib lib)
{
	t_ed_sprite *ed_sprite;
	int			index;
	int			sc_index;
	int			spr_index;

	index = 0;
	sc_index = 0;
	spr_index = -1;
	ed_sprite = doom->game_design.sp_head->next;
	while (sc_index < doom->game_design.sc_len && ed_sprite)
	{
		if (ed_sprite->sector == sc_index && spr_index == -1)
			spr_index = index;
		if (ed_sprite->sector == sc_index)
			set_sprite_values(doom, &lib.sprites[index], ed_sprite, &index);
		if (ed_sprite->next == NULL)
		{
			set_sector_sprite_values(&doom->lib.sector[sc_index], \
				&spr_index, &sc_index, index);
			ed_sprite = doom->game_design.sp_head->next;
			sc_index++;
		}
		else
			ed_sprite = ed_sprite->next;
	}
}

void			set_sprite_lib(t_doom *doom)
{
	t_ed_sprite *ed_sprite;
	t_lib		lib;
	int			index;
	int			sc_index;
	int			spr_index;

	lib.sprites = \
		(t_sprite*)ft_memalloc(sizeof(t_sprite) * doom->game_design.spr_len);
	if (lib.sprites == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	sort_sprite_per_sector(doom, lib);
	delete_list(doom);
	doom->lib.sprites = lib.sprites;
	doom->total_sprites = doom->game_design.spr_len;
}
