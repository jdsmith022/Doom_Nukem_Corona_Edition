/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events_game_editor.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 20:14:18 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void		set_sector_settings(t_doom *doom)
{
	int sector;

	sector = doom->lib.sidedef[doom->game_design.i_sd].sector;
	doom->lib.sector[sector].light_level = doom->game_design.light_level / 10;
	doom->lib.sector[sector].light = TRUE;
	doom->lib.sector[sector].height_ceiling = doom->game_design.ceiling_height;
	doom->lib.sector[sector].height_floor = doom->game_design.floor_height;
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
	else if (x > CROSS_SC_X && x < CROSS_SC_X + FRAME_WIDTH && \
	y > CROSS_SC_Y && y < CROSS_SC_Y + FRAME_HEIGHT)
		set_sector_settings(doom);
}

static void		mouse_press_object(t_doom *doom, int x, int y)
{
	if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF)
		put_sprite(doom, x, y);
	else if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH \
	&& y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT &&
	doom->game_design.i_spr_tex - 1 >= 0)
		doom->game_design.i_spr_tex--;
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && \
	y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT && \
	doom->game_design.i_spr_tex + 1 < 5)
		doom->game_design.i_spr_tex++;
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SC_Y && y < RM_SC_Y + FRAME_HEIGHT && \
	doom->game_design.len_spr > 0)
		delete_sprite(doom);
}

void			mouse_press_game_editor(t_doom *doom, int x, int y)
{
	mouse_press_sidedef(doom, x, y);
	mouse_press_sector(doom, x, y);
	mouse_press_object(doom, x, y);
}
