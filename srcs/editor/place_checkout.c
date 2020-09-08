/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   place_checkout.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 13:36:40 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void			check_placement(t_doom *doom,
						t_ed_sidedef *sidedef, t_line line)
{
	if (point_line_distance(doom->game_design.ed_sprite->pos, \
		sidedef->line) < 10.0)
	{
		if (line.start.x == line.end.x)
		{
			if (doom->game_design.ed_sprite->pos.x == line.start.x)
				doom->game_design.ed_sprite->pos.y -= 10;
			else
				doom->game_design.ed_sprite->pos.y += 10;
		}
		else
		{
			if (doom->game_design.ed_sprite->pos.y == line.start.y)
				doom->game_design.ed_sprite->pos.x -= 10;
			else
				doom->game_design.ed_sprite->pos.x += 10;
		}
	}
}

static void			set_checkout_location(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	t_line			line;
	t_line			ray;

	sidedef = doom->game_design.sd_head->next;
	while (sidedef->next != NULL)
		sidedef = sidedef->next;
	while (point_distance(sidedef->line.start, sidedef->line.end) < 30.0)
		sidedef = sidedef->previous;
	line.start = sidedef->line.start;
	line.end = sidedef->line.end;
	create_mid_points(&line, 15);
	ray.start = line.start;
	ray = set_ray(doom, ray);
	if (check_sector_in_sector(doom, ray) == TRUE)
		doom->game_design.ed_sprite->pos = line.start;
	else
		doom->game_design.ed_sprite->pos = line.end;
	check_placement(doom, sidedef, line);
	doom->game.editor = FALSE;
}

static void			set_checkout_sprite(t_doom *doom)
{
	int id;

	id = doom->game_design.spr_len;
	doom->game_design.ed_sprite->id = id;
	doom->game_design.ed_sprite->sector = doom->game_design.cur_sector;
	doom->game_design.cur_sprite = id;
	doom->game_design.spr_len++;
	doom->game_design.ed_sprite->type = \
		doom->game_design.ed_spr_index[doom->game_design.spr_tex];
	set_checkout_location(doom);
	doom->game_design.ed_sprite->next = NULL;
}

void				place_checkout(t_doom *doom)
{
	t_line		ray;
	int			id;
	t_ed_sprite *prev;

	while (doom->game_design.ed_sprite->next != NULL)
		doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
	doom->game_design.ed_sprite->next =\
		(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
	if (!doom->game_design.ed_sprite->next)
		doom_exit_failure(doom, "error: malloc sprite in editor\n");
	prev = doom->game_design.ed_sprite;
	doom->game_design.ed_sprite = doom->game_design.ed_sprite->next;
	doom->game_design.ed_sprite->previous = prev;
	set_checkout_sprite(doom);
}
