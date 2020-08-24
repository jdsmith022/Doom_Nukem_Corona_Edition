#include "../../includes/doom.h"
#include "game_editor.h"

void	init_diff(t_line *diff)
{
	diff->start.x = 0;
	diff->start.y = 0;
	diff->end.x = INFINITY;
	diff->end.y = INFINITY;
}

void	check_corners(t_line line, t_line *diff)
{
	if (line.start.x > diff->start.x)
		diff->start.x = line.start.x;
	if (line.end.x > diff->start.x)
		diff->start.x = line.end.x;
	if (line.start.x < diff->end.x)
		diff->end.x = line.start.x;
	if (line.end.x < diff->end.x)
		diff->end.x = line.end.x;
	if (line.start.y > diff->start.y)
		diff->start.y = line.start.y;
	if (line.end.y > diff->start.y)
		diff->start.y = line.end.y;
	if (line.start.y < diff->end.y)
		diff->end.y = line.start.y;
	if (line.end.y < diff->end.y)
		diff->end.y = line.end.y;
}

t_line	corners(t_doom *doom)
{
	int i;
	int side;
	t_line	diff;

	init_diff(&diff);
	i = 0;
	while (i < EDIT.w_len)
	{
		check_corners(SIDEDEF[i].line, &diff);
		i++;
	}
	i = 0;
	while (i < EDIT.o_len)
	{
		side = 0;
		while (side < 4)
		{
			check_corners(OBJECT[i].lines[side], &diff);
			side++;
		}
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

	diff = corners(doom);
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
