#include "../../includes/doom.h"
#include "game_editor.h"

void    mouse_press_map(t_doom *doom, int x, int y)
{
    if (x > MINUS_X && x < MINUS_X + FRAME_WIDTH && y > MINUS_Y && y < MINUS_Y + FRAME_HEIGHT)
	{
		if (EDIT.s_len > 0)
			del_sector(doom);
	}
	else if (x > PLUS_X && x < PLUS_X + FRAME_WIDTH && y > PLUS_Y && y < PLUS_Y + FRAME_HEIGHT)
			add_sector(doom);
	else if (x > AR_RIGHT_M_X && x < AR_RIGHT_M_X + FRAME_WIDTH && y > AR_RIGHT_M_Y && y < AR_RIGHT_M_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].diff_x -= 10;
	else if (x > AR_LEFT_M_X && x < AR_LEFT_M_X + FRAME_WIDTH && y > AR_LEFT_M_Y && y < AR_LEFT_M_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].diff_x += 10;
	else if (x > AR_DOWN_M_X && x < AR_DOWN_M_X + FRAME_WIDTH && y > AR_DOWN_M_Y && y < AR_DOWN_M_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].diff_y += 10;
	else if (x > AR_UP_M_X && x < AR_UP_M_X + FRAME_WIDTH && y > AR_UP_M_Y && y < AR_UP_M_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].diff_y -= 10;
    else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && EDIT.pl_pos == 0)
		add_sidedef(doom, x, y);
    else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && EDIT.pl_pos == 1)
	{
		EDIT.pl_x = x;
		EDIT.pl_y = y;
		EDIT.pl_sec = EDIT.cur_sec;
		EDIT.pl_pos = 0;
	}
}

void    mouse_press_sector(t_doom *doom, int x, int y)
{
	if (x > D_45_X && x < D_45_X + FRAME_WIDTH && y > D_45_Y && y < D_45_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].slope_floor = 45;
	else if (x > D_M45_X && x < D_M45_X + FRAME_WIDTH && y > D_M45_Y && y < D_M45_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].slope_floor = -45;
	else if (x > STRAIGHT_X && x < STRAIGHT_X + FRAME_WIDTH && y > STRAIGHT_Y && y < STRAIGHT_Y + FRAME_HEIGHT)
		SECTOR[EDIT.cur_sec].slope_floor = 0;
	else if (x > HF_X && x < HF_X + HF_LEN && y > HF_Y && y < HF_Y + HF_HEIGHT)
	{
		SECTOR[EDIT.cur_sec].height_floor = (float)(x - HF_X) / HF_LEN * HF_DIFF + HF_MIN;
	}
	else if (x > HC_X && x < HC_X + HC_LEN && y > HC_Y && y < HC_Y + HC_HEIGHT)
	{
		SECTOR[EDIT.cur_sec].height_ceiling = (float)(x - HC_X) / HC_LEN * HC_DIFF + HC_MIN;
	}
	else if (x > LL_X && x < LL_X + LL_LEN && y > LL_Y && y < LL_Y + LL_HEIGHT)
	{
		SECTOR[EDIT.cur_sec].light_level = (float)(x - LL_X) / LL_LEN * LL_DIFF + LL_MIN;
	}
	else if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH && y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT)
	{
		if (EDIT.cur_sec > 0)
		{
			EDIT.cur_sec--;
			EDIT.cur_sd = SECTOR[EDIT.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && y > AR_RIGHT_Y && y < AR_RIGHT_Y + FRAME_HEIGHT)
	{
		if (EDIT.cur_sec < EDIT.s_len)
		{
			EDIT.cur_sec++;
			EDIT.cur_sd = SECTOR[EDIT.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_RIGHT_TF_X && x < AR_RIGHT_TF_X + FRAME_WIDTH && y > AR_RIGHT_TF_Y && y < AR_RIGHT_TF_Y + FRAME_HEIGHT)
	{
		if (doom->lib.len_tex_lib  > SECTOR[EDIT.cur_sec].txt_floor + 1)
		SECTOR[EDIT.cur_sec].txt_floor++;
	}
	else if (x > AR_LEFT_TF_X && x < AR_LEFT_TF_X + FRAME_WIDTH && y > AR_LEFT_TF_Y && y < AR_LEFT_TF_Y + FRAME_HEIGHT)
	{
		if (SECTOR[EDIT.cur_sec].txt_floor - 1 >= 0)
		SECTOR[EDIT.cur_sec].txt_floor--;
	}
	else if (x > AR_RIGHT_TC_X && x < AR_RIGHT_TC_X + FRAME_WIDTH && y > AR_RIGHT_TC_Y && y < AR_RIGHT_TC_Y + FRAME_HEIGHT)
	{
		if (doom->lib.len_tex_lib > SECTOR[EDIT.cur_sec].txt_ceiling + 1)
			SECTOR[EDIT.cur_sec].txt_ceiling++;
	}
	else if (x > AR_LEFT_TC_X && x < AR_LEFT_TC_X + FRAME_WIDTH && y > AR_LEFT_TC_Y && y < AR_LEFT_TC_Y + FRAME_HEIGHT)
	{
		if (SECTOR[EDIT.cur_sec].txt_ceiling - 1 >= 0)
			SECTOR[EDIT.cur_sec].txt_ceiling--;
	}
}

void    mouse_press_sidedef(t_doom *doom, int x, int y)
{
    if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
	{
		if (EDIT.cur_sd + 1< SECTOR[EDIT.cur_sec].i_sidedefs + SECTOR[EDIT.cur_sec].n_sidedefs)
					EDIT.cur_sd++;
	}
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
	{
		if (EDIT.cur_sd > SECTOR[EDIT.cur_sec].i_sidedefs - 1)
			EDIT.cur_sd--;
	}
	else if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
	{
		if (EDIT.s_len > 0)
			add_portal(doom, 0);
	}
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && y > RM_SD_Y && y < RM_SD_Y + FRAME_HEIGHT)
	{
		if (EDIT.cur_sd >= SECTOR[EDIT.cur_sec].i_sidedefs)
			del_sidedef(doom);
	}
	else if (EDIT.portal_sec != -1 && x > AR_LEFT_SC_X && x < AR_LEFT_SC_X + FRAME_WIDTH && y > AR_LEFT_SC_Y && y < AR_LEFT_SC_Y + FRAME_HEIGHT)
		add_portal(doom, -1);
	else if (EDIT.portal_sec != -1 && x > AR_RIGHT_SC_X && x < AR_RIGHT_SC_X + FRAME_WIDTH && y > AR_RIGHT_SC_Y && y < AR_RIGHT_SC_Y + FRAME_HEIGHT)	
		add_portal(doom, 1);
	else if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1 && x > AR_LEFT_TS1_X && x < AR_LEFT_TS1_X + FRAME_WIDTH && y > AR_LEFT_TS1_Y && y < AR_LEFT_TS1_Y + FRAME_HEIGHT)
	{
		if (SIDEDEF[EDIT.cur_sd].txt_1 - 1 >= -1)
			SIDEDEF[EDIT.cur_sd].txt_1--;
	}
	else if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1 && x > AR_RIGHT_TS1_X && x < AR_RIGHT_TS1_X + FRAME_WIDTH && y > AR_RIGHT_TS1_Y && y < AR_RIGHT_TS1_Y + FRAME_HEIGHT)
	{
		if (doom->lib.len_tex_lib > SIDEDEF[EDIT.cur_sec].txt_1 + 1)
		
		SIDEDEF[EDIT.cur_sd].txt_1++;
	}
	else if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT)
	{
		if (SIDEDEF[EDIT.cur_sd].txt_2 - 1 >= -1)
			SIDEDEF[EDIT.cur_sd].txt_2--;
	}
	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT)
	{
		if (doom->lib.len_tex_lib > SIDEDEF[EDIT.cur_sec].txt_2 + 1)
			SIDEDEF[EDIT.cur_sd].txt_2++;
	}
	else if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1 && x > AR_LEFT_TS3_X && x < AR_LEFT_TS3_X + FRAME_WIDTH && y > AR_LEFT_TS3_Y && y < AR_LEFT_TS3_Y + FRAME_HEIGHT)
	{
		if (SIDEDEF[EDIT.cur_sd].txt_3 - 1 >= -1)
		SIDEDEF[EDIT.cur_sd].txt_3--;
	}
	else if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1 && x > AR_RIGHT_TS3_X && x < AR_RIGHT_TS3_X + FRAME_WIDTH && y > AR_RIGHT_TS3_Y && y < AR_RIGHT_TS3_Y + FRAME_HEIGHT)
	{
		if (doom->lib.len_tex_lib > SIDEDEF[EDIT.cur_sec].txt_3 + 1)
			SIDEDEF[EDIT.cur_sd].txt_3++;
	}
	
}

void	mouse_press_game_editor(t_doom *doom, int x, int y)
{
	if (EDIT.portal_sec != -1 && 
	((x < AR_LEFT_SC_X || (x > AR_LEFT_SC_X + FRAME_WIDTH && x < AR_RIGHT_SC_X) || x > AR_RIGHT_SC_X + FRAME_WIDTH)
	|| (y < AR_LEFT_SC_Y || y > AR_LEFT_SC_Y + FRAME_HEIGHT)))
	{
		EDIT.portal_sec = -1;
		EDIT.portal_sd = -1;

	}
    mouse_press_map(doom, x, y);
    mouse_press_sector(doom, x, y);
	if (EDIT.w_len > 0)
    	mouse_press_sidedef(doom, x, y);
}
