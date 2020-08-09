#include "../../includes/doom.h"
#include "game_editor.h"


void		del_sector(t_doom *doom)
{
	int i;
	int n_sidedef;

	i =	SECTOR[EDIT.cur_sec].i_sidedefs;
	while (i < SECTOR[EDIT.cur_sec].i_sidedefs + SECTOR[EDIT.cur_sec].n_sidedefs)
	{
		if (SIDEDEF[i].opp_sidedef != -1) //causes segfault: why?
		{
			SIDEDEF[SIDEDEF\
			[i].opp_sidedef].opp_sidedef = -1;
			SIDEDEF[SIDEDEF\
			[i].opp_sidedef].opp_sector = -1;
		}
		i++;
	}
	i = SECTOR[EDIT.cur_sec].i_sidedefs;
	while (i < EDIT.w_len - SECTOR[EDIT.cur_sec].n_sidedefs)
	{
		SIDEDEF[i] = SIDEDEF[i + SECTOR[EDIT.cur_sec].n_sidedefs];
		i++;
	}
	EDIT.w_len -= SECTOR[EDIT.cur_sec].n_sidedefs;
	i = EDIT.cur_sec;
	n_sidedef = SECTOR[i].n_sidedefs;
	while (i < EDIT.s_len)
	{
		SECTOR[i] = SECTOR[i + 1];
		SECTOR[i].i_sidedefs -= n_sidedef;
		i++;
	}
	if (EDIT.cur_sec == EDIT.s_len)
		EDIT.cur_sec--;
	EDIT.s_len--;
	EDIT.cur_sd = SECTOR[EDIT.cur_sec].i_sidedefs - 1;
}

t_sector *cpy_sector(t_sector *sector, int *s_size)
{
	t_sector	*new;
	int			i;

	new = (t_sector*)malloc(sizeof(t_sector) * *s_size * 2);
	i = 0;
	while (i < *s_size)
	{
		new[i] = sector[i];
		i++;
	}
	free(sector);
	*s_size *= 2;
	return (new);
}


void	add_sector(t_doom *doom)
{

		if (EDIT.s_len + 1 == EDIT.s_size)
				SECTOR = cpy_sector(SECTOR, &EDIT.s_size);
		EDIT.s_len++;
		SECTOR[EDIT.s_len].slope_floor = 0;
		SECTOR[EDIT.s_len].slope_ceiling = 0;
		SECTOR[EDIT.s_len].height_ceiling = 0;
		SECTOR[EDIT.s_len].height_floor = 0;
		SECTOR[EDIT.s_len].txt_floor = 0;
		SECTOR[EDIT.s_len].txt_ceiling = 0;
		SECTOR[EDIT.s_len].i_sidedefs = EDIT.w_len;
		SECTOR[EDIT.s_len].n_sidedefs = 0;
		SECTOR[EDIT.s_len].diff_x = 0;
		SECTOR[EDIT.s_len].diff_y = 0;
		SECTOR[EDIT.s_len].outside = 0;
		SECTOR[EDIT.s_len].light_level = 10;

}
