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

void	set_spr_checkout(t_sprite *sprite)
{
	sprite->index = SPR_CHECKOUT;
	sprite->size = X_LARGE;
	sprite->textures[0] = 114;
	sprite->textures[1] = 117;
	sprite->textures[2] = 114;
	sprite->textures[3] = 117;
	sprite->block = BLOCK;
	sprite->action = 50;
	set_spr_lines(sprite, LENGTH_LARGE);
}

void	set_spr_health_pack_pl(t_sprite *sprite)
{
	sprite->index = HEALTH_PACK_PLUS;
	sprite->size = SMALL;
	sprite->textures[0] = 14;
	sprite->textures[1] = 14;
	sprite->textures[2] = 14;
	sprite->textures[3] = 14;
	sprite->block = NO_BLOCK;
	sprite->action = 1;
	set_spr_lines(sprite, LENGTH_SMALL);
}

void	set_spr_health_pack(t_sprite *sprite)
{
	sprite->index = HEALTH_PACK;
	sprite->size = SMALL;
	sprite->textures[0] = 15;
	sprite->textures[1] = 15;
	sprite->textures[2] = 15;
	sprite->textures[3] = 15;
	sprite->block = NO_BLOCK;
	sprite->action = 2;
	set_spr_lines(sprite, LENGTH_SMALL);
}

void	set_spr_corona(t_sprite *sprite)
{
	sprite->index = CORONA;
	sprite->size = SMALL;
	sprite->textures[0] = 19;
	sprite->textures[1] = 19;
	sprite->textures[2] = 19;
	sprite->textures[3] = 19;
	sprite->block = NO_BLOCK;
	sprite->action = 4;
	set_spr_lines(sprite, LENGTH_SMALL);
}
