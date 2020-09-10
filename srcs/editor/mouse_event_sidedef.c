/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_event_sidedef.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 15:18:37 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"


static void		set_sidedef_to_prev(t_doom *doom)
{
	// t_ed_sidedef *sidedef;

	// sidedef = doom->game_design.ed_sidedef;
	// if (sidedef->id - 1 >= 0)
	// {
	// 	sidedef = sidedef->previous;
	// 	doom->game_design.ed_sidedef = sidedef;
	// }
}

static void		set_sidedef_to_next(t_doom *doom)
{
	// sidedef = doom->game_design.ed_sidedef;
	// if (sidedef->id + 1 < doom->game_design.sd_len)
	// {
	// 	sidedef = sidedef->next;
	// 	doom->game_design.ed_sidedef = sidedef;
	// }
}

void			mouse_press_sidedef(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && \
	y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_next(doom);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_prev(doom);
	else if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH &&
	y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game.editor = FALSE;
	// else if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	// y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT && \
	// doom->game_design.i_tex- 1 >= 0)
		//save_texture
	// else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	// y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT &&\
	// doom->game_design.i_tex+ 1 < 12)
		//save_texture
}
