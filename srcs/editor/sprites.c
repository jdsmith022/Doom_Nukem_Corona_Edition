#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void	put_sprite(t_doom *doom, int x, int y)
{
	t_point		pos;
	int			id;
	t_ed_sprite *prev;

	pos.x = x;
	pos.y = y;
	if (check_sector_in_sector(doom, pos) == TRUE)
	{
		id = doom->game_design.spr_len;
		while (doom->game_design.ed_sprite->next != NULL)
			doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->next =\
			(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
		if (!doom->game_design.ed_sprite->next)
			doom_exit_failure(doom, "error: malloc sprite in editor\n");
		prev = doom->game_design.ed_sprite;
		doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->id = id;
		doom->game_design.ed_sprite->pos = pos;
		doom->game_design.ed_sprite->sector = doom->game_design.pl_pos;
		doom->game_design.ed_sprite->type = \
			doom->game_design.ed_spr_index[doom->game_design.spr_tex];
		doom->game_design.ed_sprite->next = NULL;
		doom->game_design.cur_sprite = id;
		doom->game_design.spr_len++;
	}
}