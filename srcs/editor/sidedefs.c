#include "../../includes/doom.h"
#include "game_editor.h"

void		del_sidedef(t_doom *doom)
{
	int i;

	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef != -1)
	{
		doom->game_design.sidedef[doom->game_design.sidedef\
		[doom->game_design.cur_sd].opp_sidedef].opp_sidedef = -1;
		doom->game_design.sidedef[doom->game_design.sidedef\
		[doom->game_design.cur_sd].opp_sidedef].opp_sector = -1;
	}
	i = doom->game_design.cur_sec + 1;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_sidedefs--;
		i++;
	}
	i = doom->game_design.cur_sd;
	while (i < doom->game_design.w_len - 1)
	{
		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + 1];
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs--;
	doom->game_design.w_len--;
	doom->game_design.cur_sd--;
}

t_sidedef	*cpy_sidedef(t_doom *doom, t_sidedef *sidedef, int *w_size)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * *w_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < *w_size)
	{
		new[i] = sidedef[i];
		i++;
	}
	free(sidedef);
	*w_size *= 2;
	return (new);
}

void		mv_sidedef(t_sidedef **sidedef, int w_len, int id)
{
	int			i;
	t_sidedef	safe;
	t_sidedef	safe2;

	i = id;
	safe = sidedef[0][i];
	sidedef[0][i] = sidedef[0][w_len];
	i++;
	while (i < w_len)
	{
		safe2 = sidedef[0][i];
		sidedef[0][i] = safe;
		safe = safe2;
		i++;
	}
	sidedef[0][i] = safe;
}

void		correct_count(t_doom *doom)
{
	int i;

	i = doom->game_design.cur_sec + 1;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_sidedefs++;
		i++;
	}
}

void		add_sidedef_to_array(int id, int x, int y, t_doom *doom)
{
	doom->game_design.sidedef[doom->game_design.w_len].line.end.x = \
	x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	doom->game_design.sidedef[doom->game_design.w_len].line.end.y = \
	y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	doom->game_design.sidedef[doom->game_design.w_len].id = id;
	doom->game_design.sidedef[doom->game_design.w_len].sector = \
	doom->game_design.cur_sec;
	doom->game_design.sidedef[doom->game_design.w_len].opp_sidedef = -1;
	doom->game_design.sidedef[doom->game_design.w_len].opp_sector = -1;
	doom->game_design.sidedef[doom->game_design.w_len].txt_1 = 0;
	doom->game_design.sidedef[doom->game_design.w_len].txt_2 = 0;
	doom->game_design.sidedef[doom->game_design.w_len].txt_3 = 0;
	doom->game_design.sidedef[doom->game_design.w_len].action = 0;
	if (doom->game_design.cur_sec != doom->game_design.s_len)
		mv_sidedef(&doom->game_design.sidedef, doom->game_design.w_len, \
		doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs);
	correct_count(doom);
	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs++;
	doom->game_design.cur_sd = doom->game_design.cur_sec !=\
	doom->game_design.s_len ?
	doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs \
	: doom->game_design.w_len;
	doom->game_design.w_len++;
}

void		sidedef_init(t_doom *doom, int *start, int *id)
{
	doom->game_design.sidedef = (t_sidedef*)malloc(sizeof(t_sidedef) * 2);
	doom->game_design.w_size = 2;
	doom->game_design.w_len = 0;
	start = 0;
	id = 0;
}

void		add_sidedef(t_doom *doom, int x, int y)
{
	static int	start;
	static int	id;
	int			i;

	if (doom->game_design.sidedef == NULL)
		sidedef_init(doom, &start, &id);
	if (!start)
	{
		if (doom->game_design.w_size < doom->game_design.w_len + 1)
			doom->game_design.sidedef = cpy_sidedef(doom,\
			doom->game_design.sidedef, &doom->game_design.w_size);
		doom->game_design.sidedef[doom->game_design.w_len].line.start.x = \
		x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		doom->game_design.sidedef[doom->game_design.w_len].line.start.y = \
		y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		start = 1;
	}
	else
	{
		add_sidedef_to_array(id, x, y, doom);
		start = 0;
		id++;
	}
}
