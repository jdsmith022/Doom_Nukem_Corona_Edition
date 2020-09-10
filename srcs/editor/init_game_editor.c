/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game_editor.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 20:50:10 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void			init_lists(t_doom *doom)
{
	doom->game_design.ed_sprite = \
		(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
	if (!doom->game_design.ed_sprite)
		doom_exit_failure(doom, "error: malloc sprite in editor\n");
	doom->game_design.ed_sprite->id = 0;
	doom->game_design.ed_sprite->type = SPR_CHECKOUT;
	doom->game_design.ed_sprite->pos.x = 421;
	doom->game_design.ed_sprite->pos.y = 485;
	doom->game_design.ed_sprite->sector = 10;
	doom->game_design.sp_head = doom->game_design.ed_sprite;
	doom->lib.sector[10].n_objects = 1;
	doom->game_design.ed_sprite->next = NULL;
}

void				init_game_design(t_doom *doom)
{
	doom->game_design.i_sd = 0;
	doom->game_design.i_sd_tex = 1;
	doom->game_design.i_sector = 0;
	doom->game_design.i_sprites = 0;
	doom->game_design.i_spr_tex = 0;
	doom->game_design.len_spr = 1;
	doom->game_design.light_level = 10;
	doom->game_design.custom_level = TRUE;
	doom->pos.x = 229;
	doom->pos.y = 64;
	init_lists(doom);
}
