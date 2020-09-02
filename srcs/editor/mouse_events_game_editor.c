#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void		mouse_press_map(t_doom *doom, int x, int y)
{
	t_gamedesign editor;

	editor =  doom->game_design;
	// if (x > AR_RIGHT_M_X && x < AR_RIGHT_M_X + FRAME_WIDTH && \
	// y > AR_RIGHT_M_Y && y < AR_RIGHT_M_Y + FRAME_HEIGHT)
	// 	doom->game_design.sector[doom->game_design.cur_sec].diff_x -= 10;
	// else if (x > AR_LEFT_M_X && x < AR_LEFT_M_X + FRAME_WIDTH && \
	// y > AR_LEFT_M_Y && y < AR_LEFT_M_Y + FRAME_HEIGHT)
	// 	doom->game_design.sector[doom->game_design.cur_sec].diff_x += 10;
	// else if (x > AR_DOWN_M_X && x < AR_DOWN_M_X + FRAME_WIDTH && \
	// y > AR_DOWN_M_Y && y < AR_DOWN_M_Y + FRAME_HEIGHT)
	// 	doom->game_design.sector[doom->game_design.cur_sec].diff_y += 10;
	// else if (x > AR_UP_M_X && x < AR_UP_M_X + FRAME_WIDTH && \
	// y > AR_UP_M_Y && y < AR_UP_M_Y + FRAME_HEIGHT)
	// 	doom->game_design.sector[doom->game_design.cur_sec].diff_y -= 10;
	if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.edit_sector == FALSE && editor.open_connection == TRUE)
		check_connection(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.edit_sector == FALSE && editor.open_connection == FALSE)
		add_sidedef(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.pl_pos == 0 && editor.object_bar == 1)
		// add_object(doom, x, y);
	if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.pl_pos == 1)
		add_player(doom, x, y);
}

// static void		mouse_press_sector_txt(t_doom *doom, int x, int y)
// {
// 	if (x > AR_RIGHT_TF_X && x < AR_RIGHT_TF_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_TF_Y && y < AR_RIGHT_TF_Y + FRAME_HEIGHT)
// 		change_texture(doom, \
// 		&(doom->game_design.sector[doom->game_design.cur_sec].txt_floor), 1);
// 	else if (x > AR_LEFT_TF_X && x < AR_LEFT_TF_X + FRAME_WIDTH && \
// 	y > AR_LEFT_TF_Y && y < AR_LEFT_TF_Y + FRAME_HEIGHT)
// 		change_texture(doom, \
// 		&(doom->game_design.sector[doom->game_design.cur_sec].txt_floor), -1);
// 	else if (x > AR_RIGHT_TC_X && x < AR_RIGHT_TC_X + FRAME_WIDTH && \
// 	y > AR_RIGHT_TC_Y && y < AR_RIGHT_TC_Y + FRAME_HEIGHT)
// 		change_texture(doom, \
// 		&(doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling), 1);
// 	else if (x > AR_LEFT_TC_X && x < AR_LEFT_TC_X + FRAME_WIDTH && \
// 	y > AR_LEFT_TC_Y && y < AR_LEFT_TC_Y + FRAME_HEIGHT)
// 		change_texture(doom, \
// 		&(doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling), -1);
// }

static void		mouse_press_sector(t_doom *doom, int x, int y)
{
	if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SD_Y && y < RM_SD_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.sc_len > 0)
			delete_sector(&(doom->game_design));
	}
	else if (x > HF_X && x < HF_X + HF_LEN && y > HF_Y && y < HF_Y + HF_HEIGHT)
		doom->game_design.floor_height = \
			(float)(x - HF_X) / HF_LEN * HF_DIFF + HF_MIN;
	else if (x > HC_X && x < HC_X + HC_LEN && y > HC_Y && y < HC_Y + HC_HEIGHT)
		doom->game_design.ceiling_height = \
		(float)(x - HC_X) / HC_LEN * HC_DIFF + HC_MIN;
	else if (x > LL_X && x < LL_X + LL_LEN && y > LL_Y && y < LL_Y + LL_HEIGHT)
		doom->game_design.light_level = \
		(float)(x - LL_X) / LL_LEN * LL_DIFF + LL_MIN;
}

static void		mouse_press_object(t_doom *doom, int x, int y)
{
	// if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH \
	// && y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
	// 	// object_change(doom, 1);
	// else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	// y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
	// 	// object_change(doom, -1);
	// if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	// y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT)
	// 	object_texture(doom, -1);
	// else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	// y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT)
	// 	object_texture(doom, 1);
	// else if (x > DEL_OBJ_X && x < DEL_OBJ_X + FRAME_WIDTH && \
	// y > DEL_OBJ_Y && y < DEL_OBJ_Y + FRAME_HEIGHT)
	// {
	// 	if (doom->game_design.cur_obj >= \
	// 	doom->game_design.sector[doom->game_design.cur_sec].i_objects)
	// 		del_obj(doom);
	// }
}

void			mouse_press_game_editor(t_doom *doom, int x, int y)
{
	mouse_press_map(doom, x, y);
	mouse_press_sector(doom, x, y);
	if (doom->game_design.edit_sector == TRUE)
	{
		if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && \
			y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game_design.pl_pos = doom->game_design.pl_pos == 0 ? 1 : 0;
		mouse_press_sidedef(doom, x, y);
		mouse_press_object(doom, x, y);
	}
}
