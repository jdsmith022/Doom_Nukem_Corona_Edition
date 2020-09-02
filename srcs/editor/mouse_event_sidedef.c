#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

// static void	mouse_press_sidedef_txt2(t_doom *doom, int x, int y)
// {
// 	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
// 	!= -1 && x > AR_LEFT_TS3_X && x < AR_LEFT_TS3_X + FRAME_WIDTH && \
// 	y > AR_LEFT_TS3_Y && y < AR_LEFT_TS3_Y + FRAME_HEIGHT)
// 		change_texture(doom,\
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_3), -1);
// 	else if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
// 	!= -1 && x > AR_RIGHT_TS3_X && x < AR_RIGHT_TS3_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_TS3_Y && y < AR_RIGHT_TS3_Y + FRAME_HEIGHT)
// 		change_texture(doom,\
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_3), 1);
// }

// void		mouse_press_sidedef_txt(t_doom *doom, int x, int y)
// {
// 	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
// 	!= -1 && x > AR_LEFT_TS1_X && x < AR_LEFT_TS1_X + FRAME_WIDTH && \
// 	y > AR_LEFT_TS1_Y && y < AR_LEFT_TS1_Y + FRAME_HEIGHT)
// 		change_texture(doom,\
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_1), -1);
// 	else if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef\
// 	!= -1 && x > AR_RIGHT_TS1_X && x < AR_RIGHT_TS1_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_TS1_Y && y < AR_RIGHT_TS1_Y + FRAME_HEIGHT)
// 		change_texture(doom,\
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_1), 1);
// 	else if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
// 	y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT)
// 		change_texture(doom,\
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_2), -1);
// 	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT)
// 		change_texture(doom, \
// 			&(doom->game_design.sidedef[doom->game_design.cur_sd].txt_2), 1);
// 	else
// 		mouse_press_sidedef_txt2(doom, x, y);
// }

// void		mouse_press_portal(t_doom *doom, int x, int y)
// {
// 	if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && \
// 	y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
// 	{
// 		if (doom->game_design.sc_len > 0)
// 			add_portal(doom, 0);
// 	}
// 	else if (doom->game_design.portal_sec != -1 && \
// 	x > AR_LEFT_SC_X && x < AR_LEFT_SC_X + FRAME_WIDTH && \
// 	y > AR_LEFT_SC_Y && y < AR_LEFT_SC_Y + FRAME_HEIGHT)
// 		add_portal(doom, -1);
// 	else if (doom->game_design.portal_sec != -1 && \
// 	x > AR_RIGHT_SC_X && x < AR_RIGHT_SC_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_SC_Y && y < AR_RIGHT_SC_Y + FRAME_HEIGHT)
// 		add_portal(doom, 1);
// }

static void	create_portal(t_doom *doom)
{
	t_ed_sidedef 	*sidedef;
	t_ed_sector		*sector;

	sidedef = doom->game_design.ed_sidedef;
	sidedef->opp_sector = doom->game_design.sc_len;
	set_sidedef_values(doom, sidedef->line);
	doom->game_design.ed_sidedef->opp_sector = sidedef->sector;
	doom->game_design.edit_sector = FALSE;
	doom->game_design.open_connection = TRUE;
	printf("create portal opp_sector = %d\n", sidedef->opp_sector);
}

static void	set_sidedef_to_prev(t_doom *doom)
{
	t_ed_sidedef *sidedef;
	
	sidedef = doom->game_design.ed_sidedef;
	if (sidedef->id - 1 >= 0)
	{
		sidedef = sidedef->previous;
		doom->game_design.cur_sd = sidedef->id;
		doom->game_design.ed_sidedef = sidedef;
	}
}

static void	set_sidedef_to_next(t_doom *doom)
{
	t_ed_sidedef *sidedef;
	
	sidedef = doom->game_design.ed_sidedef;
	if (sidedef->id + 1 < doom->game_design.sd_len)
	{
		sidedef = sidedef->next;
		doom->game_design.cur_sd = sidedef->id;
		doom->game_design.ed_sidedef = sidedef;
	}
}

void		mouse_press_sidedef(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && \
	y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_next(doom);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_prev(doom);
	else if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && \
		y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
		create_portal(doom);
	// mouse_press_portal(doom, x, y);
	// mouse_press_sidedef_txt(doom, x, y);
}
