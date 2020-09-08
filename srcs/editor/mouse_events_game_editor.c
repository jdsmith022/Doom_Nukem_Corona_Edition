/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events_game_editor.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 13:18:18 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void		add_player(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	t_line			line;
	t_line			ray;

	sidedef = doom->game_design.sd_head->next;
	while (sidedef->id != 0)
		sidedef = sidedef->next;
	line.start = sidedef->line.start;
	line.end = sidedef->line.end;
	create_mid_points(&line, 10);
	ray.start = line.start;
	ray = set_ray(doom, ray);
	if (check_sector_in_sector(doom, ray) == TRUE)
		doom->pos = line.start;
	else
		doom->pos = line.end;
	if (point_line_distance(doom->pos, sidedef->line) < 10.0)
	{
		doom->pos.x += 10;
		doom->pos.y += 10;
	}
	doom->game_design.place_checkout = TRUE;
	doom->game_design.edit_sector = FALSE;
	doom->game_design.spr_tex = 5;
	doom->i_sector = 0;
	place_checkout(doom);
}

static void		mouse_press_map(t_doom *doom, int x, int y)
{
	t_gamedesign editor;

	editor = doom->game_design;
	if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	(editor.edit_sector == TRUE || editor.place_checkout == TRUE))
		put_sprite(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
		editor.edit_sector == FALSE && editor.open_connection == TRUE)
		check_connection(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.edit_sector == FALSE && editor.open_connection == FALSE)
		add_sidedef(doom, x, y);
}

static void		mouse_press_sector(t_doom *doom, int x, int y)
{
	if (x > HF_X && x < HF_X + HF_LEN && y > HF_Y && y < HF_Y + HF_HEIGHT)
		doom->game_design.floor_height = \
			(float)(x - HF_X) / HF_LEN * HF_DIFF + HF_MIN;
	else if (x > HC_X && x < HC_X + HC_LEN && y > HC_Y && y < HC_Y + HC_HEIGHT)
		doom->game_design.ceiling_height = \
		(float)(x - HC_X) / HC_LEN * HC_DIFF + HC_MIN;
	else if (x > LL_X && x < LL_X + LL_LEN && y > LL_Y && y < LL_Y + LL_HEIGHT)
	{
		doom->game_design.light_level = \
		(float)(x - LL_X) / LL_LEN * LL_DIFF + LL_MIN;
		if (doom->game_design.light_level < 3)
			doom->game_design.light_level = 3;
		if (doom->game_design.light_level > 15)
			doom->game_design.light_level = 15;
	}
	else if (x > DEL_SECTOR_X && x < DEL_SECTOR_X + 35 && y > DEL_SECTOR_Y \
	&& y < DEL_SECTOR_Y + 35)
		delete_sector(doom);
	else if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && \
	y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT && \
	doom->game_design.place_checkout == FALSE)
		add_player(doom);
}

static void		mouse_press_object(t_doom *doom, int x, int y)
{
	if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH \
	&& y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT &&
	doom->game_design.spr_tex - 1 >= 0)
		doom->game_design.spr_tex--;
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && \
	y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT && \
	doom->game_design.spr_tex + 1 < 5)
		doom->game_design.spr_tex++;
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SC_Y && y < RM_SC_Y + FRAME_HEIGHT && \
	doom->game_design.spr_len > 0)
		delete_sprite(doom);
}

void			mouse_press_game_editor(t_doom *doom, int x, int y)
{
	mouse_press_map(doom, x, y);
	if (doom->game_design.place_checkout == FALSE)
	{
		mouse_press_sidedef_txt(doom, x, y);
		mouse_press_sidedef(doom, x, y);
	}
	if (doom->game_design.edit_sector == TRUE && \
	doom->game_design.place_checkout == FALSE)
	{
		mouse_press_sector(doom, x, y);
		mouse_press_object(doom, x, y);
	}
}
