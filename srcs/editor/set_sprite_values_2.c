/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_values_2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 19:15:04 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void		set_spr_lines(t_sprite *sprite, int length)
{
	sprite->lines = \
		(t_line*)malloc(sizeof(t_line) * 4);
	sprite->lines[0].start.x = sprite->pos.x - length;
	sprite->lines[0].start.y = sprite->pos.y - length;
	sprite->lines[0].end.x = sprite->pos.x - length;
	sprite->lines[0].end.y = sprite->pos.y + length;
	sprite->lines[1].start.x = sprite->pos.x + length;
	sprite->lines[1].start.y = sprite->pos.y - length;
	sprite->lines[1].end.x = sprite->pos.x + length;
	sprite->lines[1].end.y = sprite->pos.y + length;
	sprite->lines[2].start.x = sprite->pos.x - length;
	sprite->lines[2].start.y = sprite->pos.y - length;
	sprite->lines[2].end.x = sprite->pos.x + length;
	sprite->lines[2].end.y = sprite->pos.y - length;
	sprite->lines[3].start.x = sprite->pos.x - length;
	sprite->lines[3].start.y = sprite->pos.y + length;
	sprite->lines[3].end.x = sprite->pos.x + length;
	sprite->lines[3].end.y = sprite->pos.y + length;
}

void		set_spr_checkout(t_sprite *sprite)
{
	sprite->index = SPR_CHECKOUT;
	sprite->size = X_LARGE;
	sprite->textures[0] = 5;
	sprite->textures[1] = 9;
	sprite->textures[2] = 5;
	sprite->textures[3] = 9;
	sprite->block = BLOCK;
	sprite->action = 13;
	set_spr_lines(sprite, LENGTH_LARGE);
}

void		set_spr_health_pack_pl(t_sprite *sprite)
{
	sprite->index = HEALTH_PACK_PLUS;
	sprite->size = SMALL;
	sprite->textures[0] = 2;
	sprite->textures[1] = 2;
	sprite->textures[2] = 2;
	sprite->textures[3] = 2;
	sprite->block = NO_BLOCK;
	sprite->action = 1;
	set_spr_lines(sprite, LENGTH_SMALL);
}

void		set_spr_health_pack(t_sprite *sprite)
{
	sprite->index = HEALTH_PACK;
	sprite->size = SMALL;
	sprite->textures[0] = 3;
	sprite->textures[1] = 3;
	sprite->textures[2] = 3;
	sprite->textures[3] = 3;
	sprite->block = NO_BLOCK;
	sprite->action = 2;
	set_spr_lines(sprite, LENGTH_SMALL);
}

void		set_spr_corona(t_sprite *sprite)
{
	sprite->index = CORONA;
	sprite->size = SMALL;
	sprite->textures[0] = 4;
	sprite->textures[1] = 4;
	sprite->textures[2] = 4;
	sprite->textures[3] = 4;
	sprite->block = NO_BLOCK;
	sprite->action = 4;
	set_spr_lines(sprite, LENGTH_SMALL);
}
