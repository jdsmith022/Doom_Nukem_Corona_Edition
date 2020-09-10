/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_sprite.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 13:52:32 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void			delete_sprite(t_doom *doom)
{
	t_ed_sprite *sprite;
	t_ed_sprite *previous;

	sprite = doom->game_design.ed_sprite;
	sprite = doom->game_design.ed_sprite;
	doom->game_design.ed_sprite = sprite->previous;
	doom->game_design.ed_sprite->next = NULL;
	ft_bzero(sprite, sizeof(t_ed_sprite));
	free(sprite);
	doom->game_design.len_spr--;
	doom->game_design.cur_sprite = doom->game_design.ed_sprite->id;
}
