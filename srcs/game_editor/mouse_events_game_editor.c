#include "../../includes/doom.h"
#include "game_editor.h"

void    mouse_press_map(t_doom *doom, int x, int y)
{
    if (x > MINUS_X && x < MINUS_X + FRAME_WIDTH && y > MINUS_Y && y < MINUS_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.s_len > 0)
			del_sector(doom);
	}
	else if (x > PLUS_X && x < PLUS_X + FRAME_WIDTH && y > PLUS_Y && y < PLUS_Y + FRAME_HEIGHT)
			add_sector(doom);
	else if (x > AR_RIGHT_M_X && x < AR_RIGHT_M_X + FRAME_WIDTH && y > AR_RIGHT_M_Y && y < AR_RIGHT_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_x -= 10;
	else if (x > AR_LEFT_M_X && x < AR_LEFT_M_X + FRAME_WIDTH && y > AR_LEFT_M_Y && y < AR_LEFT_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_x += 10;
	else if (x > AR_DOWN_M_X && x < AR_DOWN_M_X + FRAME_WIDTH && y > AR_DOWN_M_Y && y < AR_DOWN_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y += 10;
	else if (x > AR_UP_M_X && x < AR_UP_M_X + FRAME_WIDTH && y > AR_UP_M_Y && y < AR_UP_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y -= 10;
    else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && doom->game_design.pl_pos == 0)
		add_sidedef(doom, x, y);
    else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && doom->game_design.pl_pos == 1)
	{
		doom->game_design.pl_x = x;
		doom->game_design.pl_y = y;
		doom->game_design.pl_sec = doom->game_design.cur_sec;
		doom->game_design.pl_pos = 0;
	}
}

void    mouse_press_sector(t_doom *doom, int x, int y)
{
	if (x > D_45_X && x < D_45_X + FRAME_WIDTH && y > D_45_Y && y < D_45_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = 45;
	else if (x > D_M45_X && x < D_M45_X + FRAME_WIDTH && y > D_M45_Y && y < D_M45_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = -45;
	else if (x > STRAIGHT_X && x < STRAIGHT_X + FRAME_WIDTH && y > STRAIGHT_Y && y < STRAIGHT_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = 0;
	else if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH && y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sec > 0)
		{
			doom->game_design.cur_sec--;
			doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && y > AR_RIGHT_Y && y < AR_RIGHT_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sec < doom->game_design.s_len)
		{
			doom->game_design.cur_sec++;
			doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd > doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1)
			doom->game_design.cur_sd--;
	}
}

void    mouse_press_sidedef(t_doom *doom, int x, int y)
{
    if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd <  doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
			doom->game_design.cur_sd++;	
	}
	else if (x > BAR_X && x < BAR_X + BAR_LEN && y > BAR_Y && y < BAR_Y + BAR_HEIGHT)
	{
		doom->game_design.sector[doom->game_design.cur_sec].height_floor = (float)(x - BAR_X) / BAR_LEN * BAR_DIFF + BAR_MIN;
	}
	else if (x > CROSS_X && x < CROSS_X + FRAME_WIDTH && y > CROSS_Y && y < CROSS_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd >= doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs)
			del_sidedef(doom);
	}
	else if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game_design.pl_pos = doom->game_design.pl_pos == 0 ? 1 : 0;
	else if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
		add_portal(doom, 0);
	else if (x > WALL_X && x < WALL_X + FRAME_WIDTH && y > WALL_X && y < WALL_X + FRAME_HEIGHT)
		doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef = -1;
	else if (doom->game_design.portal_sec != -1 && x > AR_LEFT_SC_X && x < AR_LEFT_SC_X + FRAME_WIDTH && y > AR_LEFT_SC_Y && y < AR_LEFT_SC_Y + FRAME_HEIGHT)
		add_portal(doom, -1);
	else if (doom->game_design.portal_sec != -1 &&x > AR_RIGHT_SC_X && x < AR_RIGHT_SC_X + FRAME_WIDTH && y > AR_RIGHT_SC_Y && y < AR_RIGHT_SC_Y + FRAME_HEIGHT)	
		add_portal(doom, 1);
}

void	mouse_press_game_editor(t_doom *doom, int x, int y)
{
	if (doom->game_design.portal_sec != -1 && 
	((x < AR_LEFT_SC_X || (x > AR_LEFT_SC_X + FRAME_WIDTH && x < AR_RIGHT_SC_X) || x > AR_RIGHT_SC_X + FRAME_WIDTH)
	|| (y < AR_LEFT_SC_Y || y > AR_LEFT_SC_Y + FRAME_HEIGHT)))
	{
		doom->game_design.portal_sec = -1;
		doom->game_design.portal_sd = -1;

	}
    mouse_press_map(doom, x, y);
    mouse_press_sector(doom, x, y);
    mouse_press_sidedef(doom, x, y);
}