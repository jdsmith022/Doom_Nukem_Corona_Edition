/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:04:03 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 14:04:05 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"
#include "../../includes/events.h"
#include "../../includes/render.h"


static int			check_collision(t_doom *doom, t_sidedef *sidedef,
						t_line move)
{
	if (sidedef->opp_sector == -1 || sidedef->action == 6)
		return (-1);
	if (sidedef->action == 7 && doom->own_event.trolly == FALSE)
	{
		doom->lib.font_lib.bools.trolly = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		return (-1);
	}
	if (check_floor_diff(doom, doom->i_sector, sidedef->opp_sector) == TRUE ||
	doom->own_event.scissor_lift == TRUE)
		return (-1);
	else if (check_sector_height_diff(doom, doom->i_sector, \
	sidedef->opp_sector) == FALSE)
		return (-1);
	return (0);
}

static t_sidedef	sidedef_intersection(t_doom *doom, t_line move, \
						int sector, t_point prev_intersect)
{
	int				x;
	t_sidedef		sidedef;

	x = doom->lib.sector[sector].i_sidedefs;
	while (x < doom->lib.sector[sector].n_sidedefs\
		+ doom->lib.sector[sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		sidedef.intersect = check_line_intersection(move, sidedef.line);
		if (((isnan(sidedef.intersect.x) == 0 && \
		isnan(sidedef.intersect.y) == 0)) && \
		((sidedef.intersect.x != prev_intersect.x && \
		sidedef.intersect.y != prev_intersect.y)))
			return (sidedef);
		x++;
	}
	sidedef.intersect.x = NAN;
	sidedef.intersect.y = NAN;
	return (sidedef);
}

static void			check_move_sidedef_intersection(t_doom *doom, t_line move, \
						int sector, t_point prev_intersect)
{
	int			collision;
	t_sidedef	sidedef;

	sidedef = sidedef_intersection(doom, move, sector, prev_intersect);
	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
	{
		doom->i_sector = sector;
		doom->pos = move.end;
		doom->own_event.set_step = TRUE;
	}
	else
	{
		if (sidedef.action == 2 && \
		point_line_distance(doom->pos, sidedef.line) < \
		200.0 && doom->own_event.sliding_door == -1)
			init_sliding_door(doom, &sidedef);
		collision = check_collision(doom, &sidedef, move);
		if (collision != -1)
		{
			prev_intersect = sidedef.intersect;
			sector = sidedef.opp_sector;
			check_move_sidedef_intersection(doom, move, sector, prev_intersect);
		}
	}
}

static void			move_position(t_doom *doom, t_line move, double angle)
{
	t_point		prev_intersect;

	move.start = doom->pos;
	prev_intersect.x = -1;
	prev_intersect.y = -1;
	if (sprite_collision(doom, move) == 1)
		return ;
	check_move_sidedef_intersection(doom, move, \
		doom->i_sector, prev_intersect);
}

void				set_new_position(t_doom *doom, t_event *event, double dt)
{
	t_line		move;
	double		angle;
	double		direction;

	if (event->move_pos_f == TRUE || event->move_pos_b == TRUE)
	{
		direction = MOVE_SPEED;
		if (event->move_pos_b == TRUE)
			direction = -MOVE_SPEED;
		move.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
		move.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
		angle = doom->dir_angle;
	}
	else if (event->move_pos_r == TRUE || event->move_pos_l == TRUE)
	{
		direction = 90 * PI / 180;
		if (event->move_pos_l == TRUE)
			direction = -90 * PI / 180;
		move.end.x = doom->pos.x + (MOVE_SPEED * dt) * \
			cos(doom->dir_angle + direction);
		move.end.y = doom->pos.y + (MOVE_SPEED * dt) * \
			sin(doom->dir_angle + direction);
		angle = doom->dir_angle + direction;
	}
	move_position(doom, move, angle);
}
