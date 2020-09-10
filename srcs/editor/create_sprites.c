/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 13:56:04 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static bool			check_enough_dist_to_sidedef(t_doom *doom, t_point pos)
{
	t_sidedef		sidedef;
	double			distance;
	double			min_distance;
	int				index;

	sidedef = doom->lib.sidedef[doom->game_design.i_sd];
	min_distance = INFINITY;
	while (index < doom->lib.len_sidedef)
	{
		distance = point_line_distance(pos, sidedef.line);
		if (distance < min_distance)
			min_distance = distance;
		index++;
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

static void			set_ed_sprite(t_doom *doom, t_point pos)
{
	int id;

	id = doom->game_design.len_spr;
	doom->game_design.ed_sprite->id = id;
	doom->game_design.ed_sprite->sector = doom->game_design.i_sector;
	doom->game_design.cur_sprite = id;
	doom->game_design.len_spr++;
	doom->game_design.ed_sprite->type = \
		doom->game_design.ed_spr_index[doom->game_design.i_spr_tex];
	doom->game_design.ed_sprite->pos = pos;
}

static void			set_sprite_ray(t_doom *doom, t_line *ray, int x, int y)
{
	ray->start.x = x;
	ray->start.y = y;
	*ray = set_ray(doom, *ray);
}

void				put_sprite(t_doom *doom, int x, int y)
{
	t_line		ray;
	int			id;
	t_ed_sprite *prev;

	set_sprite_ray(doom, &ray, x, y);
	if (check_sector_in_sector(doom, ray) == TRUE && \
	enough_dist_to_sprites(doom, ray.start) == TRUE && \
	check_enough_dist_to_sidedef(doom, ray.start) == TRUE)
	{
		save_current_sector(doom, ray);
		while (doom->game_design.ed_sprite->next != NULL)
			doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->next =\
			(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
		if (!doom->game_design.ed_sprite->next)
			doom_exit_failure(doom, "error: malloc sprite in editor\n");
		prev = doom->game_design.ed_sprite;
		doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
		doom->game_design.ed_sprite->previous = prev;
		set_ed_sprite(doom, ray.start);
		doom->game_design.ed_sprite->next = NULL;
	}
}
