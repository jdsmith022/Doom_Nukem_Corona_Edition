/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_values.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 20:14:18 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void	set_spr_shopper(t_sprite *sprite)
{
	sprite->index = SHOPPER;
	sprite->size = X_LARGE;
	sprite->textures[0] = 0;
	sprite->textures[1] = 6;
	sprite->textures[2] = 7;
	sprite->textures[3] = 8;
	sprite->block = BLOCK;
	sprite->action = 9;
	set_spr_lines(sprite, LENGTH_LARGE);
}

static void	set_spr_face_mask(t_sprite *sprite)
{
	sprite->index = FACE_MASK;
	sprite->size = SMALL;
	sprite->textures[0] = 1;
	sprite->textures[1] = 1;
	sprite->textures[2] = 1;
	sprite->textures[3] = 1;
	sprite->block = NO_BLOCK;
	sprite->action = 3;
	set_spr_lines(sprite, LENGTH_SMALL);
}

void		set_sprite_values(t_doom *doom, t_sprite *sprite,
				t_ed_sprite *ed_sprite, int *index)
{
	sprite->amount = 4;
	sprite->pos = ed_sprite->pos;
	sprite->sector = ed_sprite->sector;
	sprite->visible = -1;
	sprite->textures = (int*)ft_memalloc(sizeof(int) * 4);
	if (sprite->textures == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	else if (ed_sprite->type == SHOPPER)
		set_spr_shopper(sprite);
	else if (ed_sprite->type == FACE_MASK)
		set_spr_face_mask(sprite);
	else if (ed_sprite->type == HEALTH_PACK_PLUS)
		set_spr_health_pack_pl(sprite);
	else if (ed_sprite->type == HEALTH_PACK)
		set_spr_health_pack(sprite);
	else if (ed_sprite->type == CORONA)
		set_spr_corona(sprite);
	else if (ed_sprite->type == CHECKOUT)
		set_spr_checkout(sprite);
	*index += 1;
}
