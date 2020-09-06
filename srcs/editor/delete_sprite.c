#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void			init_ed_sprite(t_doom *doom)
{
	doom->game_design.ed_sprite = \
		(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
	if (!doom->game_design.ed_sprite)
		doom_exit_failure(doom, "error: malloc sprite in editor\n");
	doom->game_design.sp_head = doom->game_design.ed_sprite;
}

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
	if (doom->game_design.spr_len == 0)
		init_ed_sprite(doom);
}

static t_ed_sprite	*delete_sprite_middle(t_ed_sprite *sprite)
{
	t_ed_sprite *prev;
	t_ed_sprite *next;

	printf("delete\n");
	prev = sprite->previous;
	next = sprite->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->previous = prev;
	ft_bzero(sprite, sizeof(t_ed_sprite));
	free(sprite);
	return (next);
}

void				delete_sprites_in_sector(t_doom *doom, int sector)
{
	t_ed_sprite *sprite;
	t_ed_sprite *prev;
	t_ed_sprite *next;

	sprite = doom->game_design.sp_head->next;
	while (sprite != NULL)
	{
		if (sprite->sector == sector)
		{
			sprite = delete_sprite_middle(sprite);
			if (sprite != NULL)
				sprite->previous = prev;
			else
				init_ed_sprite(doom);
			doom->game_design.spr_len--;
			doom->game_design.cur_sprite = doom->game_design.ed_sprite->id;
		}
		else
			sprite = sprite->next;
	}
}
