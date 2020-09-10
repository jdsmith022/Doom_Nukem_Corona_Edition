/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 22:16:09 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static bool			check_enough_dist_to_sidedef(t_doom *doom, int x, int y)
{
	t_sidedef		sidedef;
	t_point			pos;
	double			distance;
	double			min_distance;
	int				index;

	pos.x = x;
	pos.y = y;
	index = 0;
	min_distance = INFINITY;
	while (index < doom->lib.len_sidedef)
	{
		sidedef = doom->lib.sidedef[index];
		distance = point_line_distance(pos, sidedef.line);
		if (distance < min_distance)
			min_distance = distance;
		index++;
	}
	if (min_distance > 20.0)
		return (TRUE);
	return (FALSE);
}

static bool			enough_dist_to_sprites(t_doom *doom, int x, int y)
{
	t_ed_sprite		*sprite;
	t_point			pos;
	double			distance;

	pos.x = x;
	pos.y = y;
	sprite = doom->game_design.sp_head;
	while (sprite != NULL)
	{
		distance = point_distance(sprite->pos, pos);
		if (distance <= 20)
			return (FALSE);
		sprite = sprite->next;
	}
	return (TRUE);
}

static void			set_ed_sprite(t_doom *doom, int x, int y)
{
	int id;

	id = doom->game_design.len_spr;
	doom->game_design.ed_sprite->id = id;
	doom->game_design.cur_sprite = id;
	doom->game_design.len_spr++;
	doom->game_design.ed_sprite->type = \
		ed_sprites[doom->game_design.i_spr_tex];
	doom->game_design.ed_sprite->pos.x = x;
	doom->game_design.ed_sprite->pos.y = y;
}

void				put_sprite(t_doom *doom, int x, int y)
{
	t_line		ray;
	int			id;
	t_ed_sprite *prev;

	if (check_sector_in_sector(doom, x, y) == TRUE && \
	enough_dist_to_sprites(doom, x, y) == TRUE && \
	check_enough_dist_to_sidedef(doom, x, y) == TRUE)
	{
		while (doom->game_design.ed_sprite->next != NULL)
			doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->next =\
			(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
		if (!doom->game_design.ed_sprite->next)
			doom_exit_failure(doom, "error: malloc sprite in editor\n");
		prev = doom->game_design.ed_sprite;
		doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->previous = prev;
		save_current_sector(doom, x, y);
		set_ed_sprite(doom, x, y);
		doom->game_design.ed_sprite->next = NULL;
	}
}
