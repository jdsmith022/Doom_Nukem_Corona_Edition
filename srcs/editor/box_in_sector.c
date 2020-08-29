#include "../../includes/doom.h"
#include "game_editor.h"

static void	init_diff(t_line *diff)
{
	diff->start.x = 0;
	diff->start.y = 0;
	diff->end.x = INFINITY;
	diff->end.y = INFINITY;
}

static void		check_corners(t_line line, t_line *diff)
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

static t_line	corners(t_doom *doom)
{
	int i;
	int side;
	t_line	diff;

	init_diff(&diff);
	i = 0;
	while (i < doom->game_design.w_len)
	{
		check_corners(doom->game_design.sidedef[i].line, &diff);
		i++;
	}
	i = 0;
	while (i < doom->game_design.o_len)
	{
		side = 0;
		while (side < 4)
		{
			check_corners(doom->game_design.object[i].lines[side], &diff);
			side++;
		}
		i++;
	}
	return (diff);
}

static void		add_corners(t_doom *doom, t_line diff)
{
	int	len;

	len = doom->game_design.w_len;
	add_sidedef(doom, diff.start.x + 1, diff.start.y + 1);
	if (len != doom->game_design.w_len)
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

void			box_in_sectors(t_doom *doom)
{
	int		i;
	int		save_x;
	int		save_y;
	int		save_cur_sec;
	t_line	diff;

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
		add_corners(doom, diff);
		doom->game_design.sector[i].diff_x = save_x;
		doom->game_design.sector[i].diff_y = save_y;
		i++;
	}
	doom->game_design.cur_sec = save_cur_sec;
}
