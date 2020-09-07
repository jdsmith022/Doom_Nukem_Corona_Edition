#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

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
	doom->game_design.spr_len--;
	doom->game_design.cur_sprite = doom->game_design.ed_sprite->id;
}

void			delete_sprites_in_sector(t_doom *doom, int sector)
{
	t_ed_sprite *sprite;
	t_ed_sprite *next;

	sprite = doom->game_design.sp_head->next;
	while (sprite != NULL)
	{
		next = sprite->next;
		ft_bzero(sprite, sizeof(t_ed_sprite));
		free(sprite);
		sprite = next;
	}
	doom->game_design.sp_head->next = NULL;
	doom->game_design.ed_sprite = doom->game_design.sp_head;
}
