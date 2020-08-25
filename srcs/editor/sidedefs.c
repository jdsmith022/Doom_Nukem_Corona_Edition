#include "../../includes/doom.h"
#include "game_editor.h"

void		del_sidedef(t_doom *doom)
{
	int i;

	if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1)
	{
		SIDEDEF[SIDEDEF\
		[EDIT.cur_sd].opp_sidedef].opp_sidedef = -1;
		SIDEDEF[SIDEDEF\
		[EDIT.cur_sd].opp_sidedef].opp_sector = -1;
	}
	i = EDIT.cur_sec + 1;
	while (i <= EDIT.s_len)
	{
		SECTOR[i].i_sidedefs--;
		i++;
	}
	i = EDIT.cur_sd;
	while (i < EDIT.w_len - 1)
	{
		SIDEDEF[i] = SIDEDEF[i + 1];
		i++;
	}
	SECTOR[EDIT.cur_sec].n_sidedefs--;
	EDIT.w_len--;
	EDIT.cur_sd--;
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

void		add_sidedef_to_array(int id, int x, int y, t_doom *doom)
{
	int i;

	SIDEDEF[EDIT.w_len].line.end.x = \
	x + SECTOR[EDIT.cur_sec].diff_x;
	SIDEDEF[EDIT.w_len].line.end.y = \
	y + SECTOR[EDIT.cur_sec].diff_y;
	SIDEDEF[EDIT.w_len].id = id;
	SIDEDEF[EDIT.w_len].sector = \
	EDIT.cur_sec;
	SIDEDEF[EDIT.w_len].opp_sidedef = -1;
	SIDEDEF[EDIT.w_len].opp_sector = -1;
	SIDEDEF[EDIT.w_len].txt_1 = 0;
	SIDEDEF[EDIT.w_len].txt_2 = 0;
	SIDEDEF[EDIT.w_len].txt_3 = 0;
	SIDEDEF[EDIT.w_len].action = 0;
	if (EDIT.cur_sec != EDIT.s_len)
		mv_sidedef(&SIDEDEF, EDIT.w_len, \
		SECTOR[EDIT.cur_sec].i_sidedefs);
	i = EDIT.cur_sec + 1;
	while (i <= EDIT.s_len)
	{
		SECTOR[i].i_sidedefs++;
		i++;
	}
	SECTOR[EDIT.cur_sec].n_sidedefs++;
	EDIT.cur_sd = EDIT.cur_sec != EDIT.s_len ? \
	SECTOR[EDIT.cur_sec].i_sidedefs \
	: EDIT.w_len;
	EDIT.w_len++;
}

void		add_sidedef(t_doom *doom, int x, int y)
{
	static int	start;
	static int	id;
	int			i;

	if (SIDEDEF == NULL)
	{
		SIDEDEF = (t_sidedef*)malloc(sizeof(t_sidedef) * 2);
		if (doom->lib.sidedef == NULL)
			doom_exit_failure(doom, "error: game design add sidedef\n");
		EDIT.w_size = 2;
		EDIT.w_len = 0;
		start = 0;
		id = 0;
	}
	if (!start)
	{
		if (EDIT.w_size < EDIT.w_len + 1)
			SIDEDEF = cpy_sidedef(doom,\
			SIDEDEF, &EDIT.w_size);
		SIDEDEF[EDIT.w_len].line.start.x = \
		x + SECTOR[EDIT.cur_sec].diff_x;
		SIDEDEF[EDIT.w_len].line.start.y = \
		y + SECTOR[EDIT.cur_sec].diff_y;
		start = 1;
	}
	else
	{
		add_sidedef_to_array(id, x, y, doom);
		start = 0;
		id++;
	}
}
