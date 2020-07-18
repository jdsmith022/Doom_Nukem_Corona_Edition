#include "../../includes/doom.h"
#include "game_editor.h"

void  init_diff(t_line *diff)
{
	diff->start.x = 0;
	diff->start.y = 0;
	diff->end.x = INFINITY;
	diff->end.y = INFINITY;
}


t_line  corners(t_doom *doom)
{
    int     i;
    t_line diff;

	i = 0;
    init_diff(&diff);
	while(i < doom->game_design.w_len)
	{
		if (doom->game_design.sidedef[i].line.start.x > diff.start.x)
			diff.start.x = doom->game_design.sidedef[i].line.start.x;
		if (doom->game_design.sidedef[i].line.end.x > diff.start.x)
			diff.start.x = doom->game_design.sidedef[i].line.end.x;
		if (doom->game_design.sidedef[i].line.start.x < diff.end.x)
			diff.end.x = doom->game_design.sidedef[i].line.start.x;
		if (doom->game_design.sidedef[i].line.end.x < diff.end.x)
			diff.end.x = doom->game_design.sidedef[i].line.end.x;
		if (doom->game_design.sidedef[i].line.start.y > diff.start.y)
			diff.start.y = doom->game_design.sidedef[i].line.start.y;
		if (doom->game_design.sidedef[i].line.end.y > diff.start.y)
			diff.start.y = doom->game_design.sidedef[i].line.end.y;
		if (doom->game_design.sidedef[i].line.start.y < diff.end.y)
			diff.end.y = doom->game_design.sidedef[i].line.start.y;
		if (doom->game_design.sidedef[i].line.end.y < diff.end.y)
			diff.end.y = doom->game_design.sidedef[i].line.end.y;
		i++;
	}
    return (diff);
}

void	add_corners(t_doom *doom, t_line diff)
{
	int	len;

	len = doom->game_design.w_len;
	add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
	if (len != doom->game_design.w_len)
	{
		del_sidedef(doom);
		add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
	}
	add_sidedef(doom, diff.start.x + 1, diff.end.y +-1);
	add_sidedef(doom, diff.start.x + 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.start.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.start.y + 1);
	add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
}

void	box_in_sectors(t_doom *doom)
{
	int i;
	int save_x;
	int save_y;
	int	save_cur_sec;
    t_line diff;

    diff = corners(doom);
	save_cur_sec = doom->game_design.cur_sec;
    i = 0;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.cur_sec = i;
		save_x = doom->game_design.sector[i].diff_x;
		save_y = doom->game_design.sector[i].diff_y;
		doom->game_design.sector[i].diff_x = 0;
		doom->game_design.sector[i].diff_y = 0;
		//test if there is still a start saved in the add sidedef function
		add_corners(doom, diff);
		doom->game_design.sector[i].diff_x = save_x;
		doom->game_design.sector[i].diff_y = save_y;
		i++;
	}
	doom->game_design.cur_sec = save_cur_sec;
}