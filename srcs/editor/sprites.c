#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void			delete_sprite(t_doom *doom)
{
	t_ed_sprite *sprite;
	t_ed_sprite *previous;

	sprite = doom->game_design.ed_sprite;
	if (doom->game_design.spr_len > 1)
	{
		if (doom->game_design.spr_len == 1)
		{
			ft_bzero(sprite, sizeof(sprite));
			free(sprite);
			doom->game_design.sp_head->next = NULL;
			sprite = doom->game_design.sp_head;
		}
		else
		{
			previous = sprite->previous;
			previous->next = NULL;
			ft_bzero(sprite, sizeof(t_ed_sprite));
			free(sprite);
			doom->game_design.ed_sprite = previous;
		}
		doom->game_design.spr_len--;
	}
}

static bool			check_enough_dist_to_sidedef(t_doom *doom, t_point pos)
{
	t_ed_sidedef	*sidedef;
	double			distance;
	double			min_distance;

	sidedef = doom->game_design.sd_head;
	min_distance = INFINITY;
	while (sidedef != NULL)
	{
		distance = point_line_distance(pos, sidedef->line);
		if (distance < min_distance)
			min_distance = distance;
		sidedef = sidedef->next;
	}
	if (min_distance > 20.0)
		return (TRUE);
	return (FALSE);
}

static bool			enough_dist_to_sprites(t_doom *doom, t_point pos)
{
	t_ed_sprite		*sprite;
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

static void				set_ed_sprite(t_doom *doom, t_point pos)
{
	int id;

	id = doom->game_design.spr_len;
	doom->game_design.ed_sprite->id = id;
	doom->game_design.ed_sprite->pos = pos;
	doom->game_design.ed_sprite->sector = doom->game_design.cur_sector;
	doom->game_design.cur_sprite = id;
	doom->game_design.spr_len++;
	doom->game_design.ed_sprite->type = \
		doom->game_design.ed_spr_index[doom->game_design.spr_tex];
	printf("sprite sector %d\n", doom->game_design.ed_sprite->sector);
}

void					put_sprite(t_doom *doom, int x, int y)
{
	t_point		pos;
	int			id;
	t_ed_sprite *prev;

	pos.x = x;
	pos.y = y;
	if (check_sector_in_sector(doom, pos) == TRUE && \
	enough_dist_to_sprites(doom, pos) == TRUE && \
	check_enough_dist_to_sidedef(doom, pos) == TRUE)
	{
		while (doom->game_design.ed_sprite->next != NULL)
			doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->next =\
			(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
		if (!doom->game_design.ed_sprite->next)
			doom_exit_failure(doom, "error: malloc sprite in editor\n");
		prev = doom->game_design.ed_sprite;
		doom->game_design.ed_sprite->previous = prev;
		doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->next = NULL;
		set_ed_sprite(doom, pos);
		if (doom->game_design.ed_sprite->type == SPR_CHECKOUT)
			doom->game.editor = FALSE;
	}
}
