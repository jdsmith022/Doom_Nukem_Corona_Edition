#include "../../includes/doom.h"
#include "game_editor.h"

void		del_sidedef(t_doom *doom)
{
	int i;

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
		// if (doom->game_design.sidedef[i].opp_sidedef != -1)
		// 	doom->game_design.sidedef[doom->game_design.sidedef[i].opp_sidedef].opp_sidedef = i;
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs--;
	doom->game_design.w_len--;
	doom->game_design.cur_sd--;
}

t_sidedef *cpy_sidedef(t_sidedef *sidedef, int *w_size)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * *w_size * 2);
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

void 	mv_sidedef(t_sidedef **sidedef, int w_len, int id)
{
	int i;
	t_sidedef safe;
	t_sidedef safe2;

	i = id;
	safe = sidedef[0][i];
	sidedef[0][i] = sidedef[0][w_len];
	i++;
	while (i < w_len)
	{
		safe2 = sidedef[0][i];
		sidedef[0][i] = safe;
		// if (sidedef[0][i].opp_sidedef != -1)
		// 	sidedef[0][sidedef[0][i].opp_sidedef].opp_sidedef = i;
		safe = safe2;
		i++;
	}
	sidedef[0][i] = safe;
}

void	add_sidedef(t_doom *doom, int x, int y)
{
	static int start;
	static int id;
	int i;

	if (doom->game_design.sidedef == NULL)
	{
		doom->game_design.sidedef = (t_sidedef*)malloc(sizeof(t_sidedef) * 2);
		doom->game_design.w_size = 2;
		doom->game_design.w_len = 0;
		id = 0;
	}
	if (!start)
	{
		if (doom->game_design.w_size < doom->game_design.w_len + 1)
				doom->game_design.sidedef = cpy_sidedef(doom->game_design.sidedef, &doom->game_design.w_size);
		doom->game_design.sidedef[doom->game_design.w_len].line.start.x = x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		doom->game_design.sidedef[doom->game_design.w_len].line.start.y = y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		start = 1;
	}
	else
	{
		doom->game_design.sidedef[doom->game_design.w_len].line.end.x = x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		doom->game_design.sidedef[doom->game_design.w_len].line.end.y = y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		doom->game_design.sidedef[doom->game_design.w_len].id = id;
		doom->game_design.sidedef[doom->game_design.w_len].sector = doom->game_design.cur_sec;
		doom->game_design.sidedef[doom->game_design.w_len].opp_sidedef = -1;
		doom->game_design.sidedef[doom->game_design.w_len].opp_sector = -1;
		if (doom->game_design.cur_sec != doom->game_design.s_len)
			mv_sidedef(&doom->game_design.sidedef, doom->game_design.w_len, doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs);
		i = doom->game_design.cur_sec + 1;
		while (i <= doom->game_design.s_len)
		{
			doom->game_design.sector[i].i_sidedefs++;
			i++;
		}
		doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs++;
		doom->game_design.cur_sd = doom->game_design.cur_sec != doom->game_design.s_len ? doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs : doom->game_design.w_len;
		doom->game_design.w_len++;
		id++;
		start = 0;
	}
}
