/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 23:31:39 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

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

static void			set_ed_sprite(t_doom *doom, t_point pos)
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
}

static void			set_sprite_ray(t_doom *doom, t_line *ray, int x, int y)
{
	ray->start.x = x;
	ray->start.y = y;
	*ray = set_ray(doom, *ray);
}

static void			set_checkout_sprite(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	t_point			sprite_pos;
	int			y_2;

	printf("hello there\n");
	sidedef = doom->game_design.sd_head->next;
	while (sidedef->next != NULL)
		sidedef = sidedef->next;
	while (sidedef->opp_sector != -1)
	{
		sidedef = sidedef->previous;
		if (sidedef->opp_sector != -1)
		{
			sprite_pos.x = ((sidedef->line.start.x + sidedef->line.end.x) / 2) + 1;
			sprite_pos.y = ((sidedef->line.start.y + sidedef->line.end.y) / 2) + 1;
			set_ed_sprite(doom, sprite_pos);
			doom->game.editor = FALSE;
			break ;
		}
	}
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
		if (doom->game_design.ed_sprite->type == SPR_CHECKOUT)
			set_checkout_sprite(doom);
	}
}
