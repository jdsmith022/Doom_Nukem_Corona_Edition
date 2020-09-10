/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_event_sidedef.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 22:02:42 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		set_sidedef_texture(t_doom *doom)
{
	doom->lib.sidedef[doom->game_design.i_sd].txt_2 = \
		ed_textures[doom->game_design.i_sd_tex];
}

static void		set_sidedef_to_prev(t_doom *doom)
{
	if (doom->lib.sidedef[doom->game_design.i_sd - 1].opp_sector != -1)
		doom->game_design.i_sd--;
	doom->game_design.i_sd--;
	if (doom->game_design.i_sd < 0)
		doom->game_design.i_sd = doom->lib.len_sidedef - 1;
	doom->game_design.i_sector = \
		doom->lib.sidedef[doom->game_design.i_sd].sector;
}

static void		set_sidedef_to_next(t_doom *doom)
{
	if (doom->lib.sidedef[doom->game_design.i_sd + 1].opp_sector != -1)
		doom->game_design.i_sd++;
	doom->game_design.i_sd++;
	if (doom->game_design.i_sd >= doom->lib.len_sidedef)
		doom->game_design.i_sd = 0;
	doom->game_design.i_sector = \
		doom->lib.sidedef[doom->game_design.i_sd].sector;
}

void			mouse_press_sidedef(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && \
	y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_next(doom);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_prev(doom);
	else if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && \
	y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game.editor = FALSE;
	else if (x > PLUS_P_X && x < PLUS_P_X + FRAME_WIDTH && \
	y > PLUS_P_Y && y < PLUS_P_Y + FRAME_HEIGHT)
		set_sidedef_texture(doom);
	else if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT && \
	doom->game_design.i_sd_tex - 1 >= 2)
		doom->game_design.i_sd_tex--;
	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT &&\
	doom->game_design.i_sd_tex + 1 < 14)
		doom->game_design.i_sd_tex++;
}
