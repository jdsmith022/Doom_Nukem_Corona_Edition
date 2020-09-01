#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		del_portal(t_doom *doom, int dir, int diff_x, int diff_y)
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
}

static void		new_portal(t_gamedesign *gd, t_doom *doom)
{
	gd->sector[gd->cur_sec].diff_x = 0;
	gd->sector[gd->cur_sec].diff_y = 0;
	add_sidedef(doom, gd->sidedef[gd->portal_sd].line.start.x,\
		gd->sidedef[gd->portal_sd].line.start.y);
	add_sidedef(doom, gd->sidedef[gd->portal_sd].line.end.x,\
		gd->sidedef[gd->portal_sd].line.end.y);
	if (gd->portal_sd > gd->cur_sd)
		gd->portal_sd++;
	gd->sidedef[gd->portal_sd].opp_sidedef = gd->cur_sd;
	gd->sidedef[gd->portal_sd].opp_sector = gd->cur_sec;
	gd->sidedef[gd->cur_sd].opp_sidedef = gd->portal_sd;
	gd->sidedef[gd->cur_sd].opp_sector = gd->portal_sec;
	if (gd->portal_sd > gd->cur_sd)
		gd->portal_sd--;
}

void			add_portal(t_doom *doom, int dir)
{
	static int diff_x;
	static int diff_y;

	if (dir != 0)
		del_portal(doom, dir, diff_x, diff_y);
	else
	{
		doom->game_design.portal_sd = doom->game_design.cur_sd;
		doom->game_design.portal_sec = doom->game_design.cur_sec;
		doom->game_design.cur_sec = doom->game_design.cur_sec > 0 \
			? doom->game_design.cur_sec - 1 : doom->game_design.s_len;
	}
	new_portal(&(doom->game_design), doom);
	// diff_x = doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	// diff_y = doom->game_design.sector[doom->game_design.cur_sec].diff_y;
}
