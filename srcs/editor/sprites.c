#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static bool enough_dist_to_sprites(t_doom *doom, t_point pos)
{
	t_ed_sprite 	*sprite;
	double			distance;

	sprite = doom->game_design.sp_head->next;
	while (sprite != NULL)
	{
		distance = point_distance(sprite->pos, pos);
		if (distance <= 20)
			return (FALSE);
		sprite = sprite->next;
	}
	return (TRUE);
}

void	put_sprite(t_doom *doom, int x, int y)
{
	t_point		pos;
	int			id;
	t_ed_sprite *prev;

	pos.x = x;
	pos.y = y;
	if (check_sector_in_sector(doom, pos) == TRUE && enough_dist_to_sprites(doom, pos) == TRUE)
	{
		printf("top of if: %d\n", doom->game_design.pl_sec);
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
		doom->game_design.ed_sprite->sector = doom->game_design.pl_sec;
		printf("when savinng sector = %d -- %d\n", doom->game_design.ed_sprite->sector, doom->game_design.pl_sec);
		doom->game_design.ed_sprite->type = \
			doom->game_design.ed_spr_index[doom->game_design.spr_tex];
		doom->game_design.ed_sprite->next = NULL;
		doom->game_design.ed_sprite->previous = prev;
		doom->game_design.cur_sprite = id;
		doom->game_design.spr_len++;
	}
}