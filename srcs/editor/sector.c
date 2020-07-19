#include "../../includes/doom.h"
#include "game_editor.h"


void		del_sector(t_doom *doom)
{
	int i;
	int n_sidedef;

	i =	doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
	while (i < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
	{
		if (doom->game_design.sidedef[i].opp_sector != -1) //causes segfault: why?
		{
			doom->game_design.sidedef[doom->game_design.sidedef\
			[doom->game_design.cur_sd].opp_sidedef].opp_sidedef = -1;
			doom->game_design.sidedef[doom->game_design.sidedef\
			[doom->game_design.cur_sd].opp_sidedef].opp_sector = -1;
		}
		i++;
	}
	i = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
	while (i < doom->game_design.w_len - doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
	{
		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs];
		i++;
	}
	doom->game_design.w_len -= doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs;
	i = doom->game_design.cur_sec;
	n_sidedef = doom->game_design.sector[i].n_sidedefs;
	while (i < doom->game_design.s_len)
	{
		doom->game_design.sector[i] = doom->game_design.sector[i + 1];
		doom->game_design.sector[i].i_sidedefs -= n_sidedef;
		i++;
	}
	if (doom->game_design.cur_sec == doom->game_design.s_len)
		doom->game_design.cur_sec--;
	doom->game_design.s_len--;
	doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
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

		if (doom->game_design.s_len + 1 == doom->game_design.s_size)
				doom->game_design.sector = cpy_sector(doom->game_design.sector, &doom->game_design.s_size);
		doom->game_design.s_len++;
		doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].txt_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].txt_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].i_sidedefs = doom->game_design.w_len;
		doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_y = 0;
		doom->game_design.sector[doom->game_design.s_len].outside = 0;
		doom->game_design.sector[doom->game_design.s_len].light_level = 10;

}
