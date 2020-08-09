#include "../../includes/doom.h"
#include "game_editor.h"

void	init_diff(t_line *diff)
{
	diff->start.x = 0;
	diff->start.y = 0;
	diff->end.x = INFINITY;
	diff->end.y = INFINITY;
}

t_line	corners(t_doom *doom, int i)
{
	t_line	diff;

	init_diff(&diff);
	while (i < EDIT.w_len)
	{
		if (SIDEDEF[i].line.start.x > diff.start.x)
			diff.start.x = SIDEDEF[i].line.start.x;
		if (SIDEDEF[i].line.end.x > diff.start.x)
			diff.start.x = SIDEDEF[i].line.end.x;
		if (SIDEDEF[i].line.start.x < diff.end.x)
			diff.end.x = SIDEDEF[i].line.start.x;
		if (SIDEDEF[i].line.end.x < diff.end.x)
			diff.end.x = SIDEDEF[i].line.end.x;
		if (SIDEDEF[i].line.start.y > diff.start.y)
			diff.start.y = SIDEDEF[i].line.start.y;
		if (SIDEDEF[i].line.end.y > diff.start.y)
			diff.start.y = SIDEDEF[i].line.end.y;
		if (SIDEDEF[i].line.start.y < diff.end.y)
			diff.end.y = SIDEDEF[i].line.start.y;
		if (SIDEDEF[i].line.end.y < diff.end.y)
			diff.end.y = SIDEDEF[i].line.end.y;
		i++;
	}
	return (diff);
}

void	add_corners(t_doom *doom, t_line diff)
{
	int	len;

	len = EDIT.w_len;
	add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
	if (len != EDIT.w_len)
	{
		del_sidedef(doom);
		add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
	}
	add_sidedef(doom, diff.start.x + 1, diff.end.y - 1);
	add_sidedef(doom, diff.start.x + 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.end.y - 1);
	add_sidedef(doom, diff.end.x - 1, diff.start.y + 1);
	add_sidedef(doom, diff.end.x - 1, diff.start.y + 1);
	add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
}

void	box_in_sectors(t_doom *doom)
{
	int		i;
	int		save_x;
	int		save_y;
	int		save_cur_sec;
	t_line	diff;

	diff = corners(doom, 0);
	save_cur_sec = EDIT.cur_sec;
	i = 0;
	while (i <= EDIT.s_len)
	{
		EDIT.cur_sec = i;
		save_x = SECTOR[i].diff_x;
		save_y = SECTOR[i].diff_y;
		SECTOR[i].diff_x = 0;
		SECTOR[i].diff_y = 0;
		add_corners(doom, diff);
		SECTOR[i].diff_x = save_x;
		SECTOR[i].diff_y = save_y;
		i++;
	}
	EDIT.cur_sec = save_cur_sec;
}
