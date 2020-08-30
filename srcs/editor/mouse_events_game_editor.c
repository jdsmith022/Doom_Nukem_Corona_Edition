#include "../../includes/doom.h"
#include "game_editor.h"
#include "sprites.h"

void	mouse_press_map(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_M_X && x < AR_RIGHT_M_X + FRAME_WIDTH && \
	y > AR_RIGHT_M_Y && y < AR_RIGHT_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_x -= 10;
	else if (x > AR_LEFT_M_X && x < AR_LEFT_M_X + FRAME_WIDTH && \
	y > AR_LEFT_M_Y && y < AR_LEFT_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_x += 10;
	else if (x > AR_DOWN_M_X && x < AR_DOWN_M_X + FRAME_WIDTH && \
	y > AR_DOWN_M_Y && y < AR_DOWN_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y += 10;
	else if (x > AR_UP_M_X && x < AR_UP_M_X + FRAME_WIDTH && \
	y > AR_UP_M_Y && y < AR_UP_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y -= 10;
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	doom->game_design.pl_pos == 0 && doom->game_design.sidedef_bar == 1)
		add_sidedef(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	doom->game_design.pl_pos == 0 && doom->game_design.object_bar == 1)
		add_object(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	doom->game_design.pl_pos == 1)
		add_player(doom, x, y);
}

void	mouse_press_sector_txt(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_TF_X && x < AR_RIGHT_TF_X + FRAME_WIDTH && \
	y > AR_RIGHT_TF_Y && y < AR_RIGHT_TF_Y + FRAME_HEIGHT)
		change_texture(doom, \
		&(doom->game_design.sector[doom->game_design.cur_sec].txt_floor), 1);
	else if (x > AR_LEFT_TF_X && x < AR_LEFT_TF_X + FRAME_WIDTH && \
	y > AR_LEFT_TF_Y && y < AR_LEFT_TF_Y + FRAME_HEIGHT)
		change_texture(doom, \
		&(doom->game_design.sector[doom->game_design.cur_sec].txt_floor), -1);
	else if (x > AR_RIGHT_TC_X && x < AR_RIGHT_TC_X + FRAME_WIDTH && \
	y > AR_RIGHT_TC_Y && y < AR_RIGHT_TC_Y + FRAME_HEIGHT)
		change_texture(doom, \
		&(doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling), 1);
	else if (x > AR_LEFT_TC_X && x < AR_LEFT_TC_X + FRAME_WIDTH && \
	y > AR_LEFT_TC_Y && y < AR_LEFT_TC_Y + FRAME_HEIGHT)
		change_texture(doom, \
		&(doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling), -1);
}

void	mouse_press_sector(t_doom *doom, int x, int y)
{
	if (x > DEL_SECTOR_X && x < DEL_SECTOR_X + FRAME_WIDTH && \
	y > DEL_SECTOR_Y && y < DEL_SECTOR_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.s_len > 0)
			del_sector(&(doom->game_design));
	}
	else if (x > ADD_SECTOR_X && x < ADD_SECTOR_X + FRAME_WIDTH && \
	y > ADD_SECTOR_Y && y < ADD_SECTOR_Y + FRAME_HEIGHT)
		add_sector(doom);
	else if (x > HF_X && x < HF_X + HF_LEN && y > HF_Y && y < HF_Y + HF_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].height_floor = \
		(float)(x - HF_X) / HF_LEN * HF_DIFF + HF_MIN;
	else if (x > HC_X && x < HC_X + HC_LEN && y > HC_Y && y < HC_Y + HC_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].height_ceiling = \
		(float)(x - HC_X) / HC_LEN * HC_DIFF + HC_MIN;
	else if (x > LL_X && x < LL_X + LL_LEN && y > LL_Y && y < LL_Y + LL_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].light_level = \
		(float)(x - LL_X) / LL_LEN * LL_DIFF + LL_MIN;
	else if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH && \
	y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT)
		change_sector(doom, 1);
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && \
	y > AR_RIGHT_Y && y < AR_RIGHT_Y + FRAME_HEIGHT)
		change_sector(doom, -1);
	mouse_press_sector_txt(doom, x, y);
}

void	mouse_press_object(t_doom *doom, int x, int y)
{
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH \
	&& y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		object_change(doom, 1);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		object_change(doom, -1);
	if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT)
		object_texture(doom, -1);
	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT)
		object_texture(doom, 1);
	else if (x > DEL_OBJ_X && x < DEL_OBJ_X + FRAME_WIDTH && \
	y > DEL_OBJ_Y && y < DEL_OBJ_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_obj >=\
		doom->game_design.sector[doom->game_design.cur_sec].i_objects)
			del_obj(doom);
	}
}

void	mouse_press_game_editor(t_doom *doom, int x, int y)
{
	if (doom->game_design.portal_sec != -1 &&\
	((x < AR_LEFT_SC_X || (x > AR_LEFT_SC_X + FRAME_WIDTH && x <\
	AR_RIGHT_SC_X) || x > AR_RIGHT_SC_X + FRAME_WIDTH) \
	|| (y < AR_LEFT_SC_Y || y > AR_LEFT_SC_Y + FRAME_HEIGHT)))
	{
		doom->game_design.portal_sec = -1;
		doom->game_design.portal_sd = -1;
	}
	if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && \
	y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game_design.pl_pos = doom->game_design.pl_pos == 0 ? 1 : 0;
	mouse_press_map(doom, x, y);
	mouse_press_sector(doom, x, y);
	if (x > SIDEDEF_BUTTON_X && x < SIDEDEF_BUTTON_X + FRAME_WIDTH && \
	y > SIDEDEF_BUTTON_Y && y < SIDEDEF_BUTTON_Y + FRAME_WIDTH)
		sidedef_object(doom);
	if (x > SECTOR_BUTTON_X && x < SECTOR_BUTTON_X + FRAME_WIDTH && \
	y > SECTOR_BUTTON_Y && y < SECTOR_BUTTON_Y + FRAME_WIDTH)
		sidedef_object(doom);
	if (doom->game_design.w_len > 0 && doom->game_design.sidedef_bar == 1)
		mouse_press_sidedef(doom, x, y);
	if (doom->game_design.object_bar == 1)
		mouse_press_object(doom, x, y);
}
