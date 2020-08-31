#include "../../includes/doom.h"
#include "game_editor.h"

static void	mouse_press_sidedef_txt2(t_doom *doom, int x, int y)
{
	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
	!= -1 && x > AR_LEFT_TS3_X && x < AR_LEFT_TS3_X + FRAME_WIDTH && \
	y > AR_LEFT_TS3_Y && y < AR_LEFT_TS3_Y + FRAME_HEIGHT)
		change_texture(doom,\
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_3), -1);
	else if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
	!= -1 && x > AR_RIGHT_TS3_X && x < AR_RIGHT_TS3_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS3_Y && y < AR_RIGHT_TS3_Y + FRAME_HEIGHT)
		change_texture(doom,\
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_3), 1);
}

void		mouse_press_sidedef_txt(t_doom *doom, int x, int y)
{
	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
	!= -1 && x > AR_LEFT_TS1_X && x < AR_LEFT_TS1_X + FRAME_WIDTH && \
	y > AR_LEFT_TS1_Y && y < AR_LEFT_TS1_Y + FRAME_HEIGHT)
		change_texture(doom,\
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_1), -1);
	else if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
	!= -1 && x > AR_RIGHT_TS1_X && x < AR_RIGHT_TS1_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS1_Y && y < AR_RIGHT_TS1_Y + FRAME_HEIGHT)
		change_texture(doom,\
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_1), 1);
	else if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT)
		change_texture(doom,\
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_2), -1);
	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT)
		change_texture(doom, \
			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_2), 1);
	else
		mouse_press_sidedef_txt2(doom, x, y);
}

void		mouse_press_portal(t_doom *doom, int x, int y)
{
	if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && \
	y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.s_len > 0)
			add_portal(doom, 0);
	}
	else if (doom->game_design.portal_sec != -1 && \
	x > AR_LEFT_SC_X && x < AR_LEFT_SC_X + FRAME_WIDTH && \
	y > AR_LEFT_SC_Y && y < AR_LEFT_SC_Y + FRAME_HEIGHT)
		add_portal(doom, -1);
	else if (doom->game_design.portal_sec != -1 && \
	x > AR_RIGHT_SC_X && x < AR_RIGHT_SC_X + FRAME_WIDTH && \
	y > AR_RIGHT_SC_Y && y < AR_RIGHT_SC_Y + FRAME_HEIGHT)
		add_portal(doom, 1);
}

void		mouse_press_sidedef(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && \
	y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		change_sidedef(doom, 1);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		change_sidedef(doom, -1);
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SD_Y && y < RM_SD_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd >= \
		doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs)
			del_sidedef(doom);
	}
	mouse_press_portal(doom, x, y);
	mouse_press_sidedef_txt(doom, x, y);
}
