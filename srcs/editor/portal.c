#include "../../includes/doom.h"
#include "game_editor.h"

void		add_portal(t_doom *doom, int dir)
{
	static int diff_x;
	static int diff_y;

	if (dir != 0)
	{
		del_sidedef(doom);
		doom->game_design.cur_sec += dir;
		if (doom->game_design.portal_sec == doom->game_design.cur_sec)
			doom->game_design.cur_sec += dir;
		if (doom->game_design.cur_sec < 0)
			doom->game_design.cur_sec = doom->game_design.s_len;
		if (doom->game_design.cur_sec > doom->game_design.s_len)
			doom->game_design.cur_sec = 0;
		if (doom->game_design.portal_sec == doom->game_design.cur_sec)
			doom->game_design.cur_sec += dir;
		doom->game_design.sector[doom->game_design.cur_sec].diff_x = diff_x;
		doom->game_design.sector[doom->game_design.cur_sec].diff_y = diff_y;
	}
	else
	{
		doom->game_design.portal_sd = doom->game_design.cur_sd;
		doom->game_design.portal_sec = doom->game_design.cur_sec;
		doom->game_design.cur_sec = doom->game_design.cur_sec > 0 ? doom->game_design.cur_sec - 1 : doom->game_design.s_len;
	}

    add_sidedef(doom,  doom->game_design.sidedef[doom->game_design.portal_sd].line.start.x, doom->game_design.sidedef[doom->game_design.portal_sd].line.start.y);
	add_sidedef(doom,  doom->game_design.sidedef[doom->game_design.portal_sd].line.end.x, doom->game_design.sidedef[doom->game_design.portal_sd].line.end.y);
	if (doom->game_design.portal_sd > doom->game_design.cur_sd)
		doom->game_design.portal_sd++;
	doom->game_design.sidedef[doom->game_design.portal_sd].opp_sidedef = doom->game_design.cur_sd;
	doom->game_design.sidedef[doom->game_design.portal_sd].opp_sector = doom->game_design.cur_sec;
	doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef = doom->game_design.portal_sd;
	doom->game_design.sidedef[doom->game_design.cur_sd].opp_sector = doom->game_design.portal_sec;
	doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = -1;
	doom->game_design.sidedef[doom->game_design.portal_sd].txt_2 = -1;
	diff_x = doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	diff_y = doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	doom->game_design.sector[doom->game_design.cur_sec].diff_x = doom->game_design.sector[doom->game_design.portal_sec].diff_x;
	doom->game_design.sector[doom->game_design.cur_sec].diff_y = doom->game_design.sector[doom->game_design.portal_sec].diff_y;
	if (doom->game_design.portal_sd > doom->game_design.cur_sd)
		doom->game_design.portal_sd--;

}