#include "../../includes/doom.h"
#include "game_editor.h"

void		del_portal(t_doom *doom, int dir, int diff_x, int diff_y)
{
	del_sidedef(doom);
	EDIT.cur_sec += dir;
	if (EDIT.portal_sec == EDIT.cur_sec)
		EDIT.cur_sec += dir;
	if (EDIT.cur_sec < 0)
		EDIT.cur_sec = EDIT.s_len;
	if (EDIT.cur_sec > EDIT.s_len)
		EDIT.cur_sec = 0;
	if (EDIT.portal_sec == EDIT.cur_sec)
		EDIT.cur_sec += dir;
	SECTOR[EDIT.cur_sec].diff_x = diff_x;
	SECTOR[EDIT.cur_sec].diff_y = diff_y;
}

void		new_portal(t_doom *doom)
{
    add_sidedef(doom, SIDEDEF[EDIT.portal_sd].line.start.x, SIDEDEF[EDIT.portal_sd].line.start.y);
	add_sidedef(doom, SIDEDEF[EDIT.portal_sd].line.end.x, SIDEDEF[EDIT.portal_sd].line.end.y);
	if (EDIT.portal_sd > EDIT.cur_sd)
		EDIT.portal_sd++;
	SIDEDEF[EDIT.portal_sd].opp_sidedef = EDIT.cur_sd;
	SIDEDEF[EDIT.portal_sd].opp_sector = EDIT.cur_sec;
	SIDEDEF[EDIT.cur_sd].opp_sidedef = EDIT.portal_sd;
	SIDEDEF[EDIT.cur_sd].opp_sector = EDIT.portal_sec;
	// SIDEDEF[EDIT.cur_sd].txt_2 = -1;
	// SIDEDEF[EDIT.portal_sd].txt_2 = -1; //neccesary?
	SECTOR[EDIT.cur_sec].diff_x = SECTOR[EDIT.portal_sec].diff_x;
	SECTOR[EDIT.cur_sec].diff_y = SECTOR[EDIT.portal_sec].diff_y;
	if (EDIT.portal_sd > EDIT.cur_sd)
		EDIT.portal_sd--;
}

void		add_portal(t_doom *doom, int dir)
{
	static int diff_x;
	static int diff_y;

	if (dir != 0)
		del_portal(doom, dir, diff_x, diff_y);
	else
	{
		EDIT.portal_sd = EDIT.cur_sd;
		EDIT.portal_sec = EDIT.cur_sec;
		EDIT.cur_sec = EDIT.cur_sec > 0 ? EDIT.cur_sec - 1 : EDIT.s_len;
	}
	new_portal(doom);
	diff_x = SECTOR[EDIT.cur_sec].diff_x;
	diff_y = SECTOR[EDIT.cur_sec].diff_y;
}