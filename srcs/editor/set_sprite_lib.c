#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

static void  set_spr_scissor_lift(t_sprite *sprite)
{
	sprite->index = SCISSOR_LIFT;
	sprite->size = MEDIUM;
	sprite->textures[0] = 7;
	sprite->textures[1] = 8;
	sprite->textures[2] = 7;
	sprite->textures[3] = 8;
	sprite->block = BLOCK;
	sprite->action = 7;
	set_spr_lines(sprite, LENGTH_LARGE);
}

static void	set_spr_shopper(t_sprite *sprite)
{
	sprite->index = SHOPPER;
	sprite->size = X_LARGE;
	sprite->textures[0] = 9;
	sprite->textures[1] = 10;
	sprite->textures[2] = 11;
	sprite->textures[3] = 12;
	sprite->block = BLOCK;
	sprite->action = 9;
	set_spr_lines(sprite, LENGTH_LARGE);
}

static void	set_spr_face_mask(t_sprite *sprite)
{
	sprite->index = SHOPPER;
	sprite->size = SMALL;
	sprite->textures[0] = 13;
	sprite->textures[1] = 13;
	sprite->textures[2] = 13;
	sprite->textures[3] = 13;
	sprite->block = NO_BLOCK;
	sprite->action = 3;
	set_spr_lines(sprite, LENGTH_SMALL);
}

static void	order_sprite_lib(t_doom *doom, t_sprite *sprite, t_ed_sprite *ed_sprite)
{
		sprite->amount = 4;
		sprite->pos = ed_sprite->pos;
		sprite->sector = ed_sprite->sector;
		sprite->textures = (int*)ft_memalloc(sizeof(int) * 4);
		if (!sprite->textures)
			doom_exit_failure(doom, "error: saving game editor info");
		if (ed_sprite->type == SCISSOR_LIFT)
			set_spr_scissor_lift(sprite);
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
		else if (ed_sprite->type == SPR_CHECKOUT)
			set_spr_checkout(sprite);

}

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
	lib.sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * doom->game_design.spr_len);
	if (lib.sprites == NULL)
		doom_exit_failure(doom, "error: saving game editor info"); // add freeing of lists
	index = 0;
	sc_index = 0;
	spr_index = -1;
	while (sc_index < doom->game_design.sc_len && ed_sprite)
	{
		if (ed_sprite->sector == sc_index)
		{
			if (spr_index == -1)
				spr_index = index;
			order_sprite_lib(doom, &lib.sprites[index], ed_sprite);
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