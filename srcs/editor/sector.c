#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

// static void			reset_portals(t_gamedesign *gd)
// {
// 	int i;

// 	i = gd->sector[gd->cur_sec].i_sidedefs;
// 	while (i < gd->sector[gd->cur_sec].i_sidedefs + \
// 	gd->sector[gd->cur_sec].n_sidedefs)
// 	{
// 		if (gd->sidedef[i].opp_sidedef != -1)
// 		{
// 			gd->sidedef[gd->sidedef[i].opp_sidedef].opp_sidedef = -1;
// 			gd->sidedef[gd->sidedef[i].opp_sidedef].opp_sector = -1;
// 		}
// 		i++;
// 	}
// }

// void				del_sector(t_gamedesign *gd)
// {
// 	int i;
// 	int n_sidedef;

// 	reset_portals(gd);
// 	i = gd->sector[gd->cur_sec].i_sidedefs;
// 	while (i < gd->w_len - gd->sector[gd->cur_sec].n_sidedefs)
// 	{
// 		gd->sidedef[i] = gd->sidedef[i + gd->sector[gd->cur_sec].n_sidedefs];
// 		i++;
// 	}
// 	gd->w_len -= gd->sector[gd->cur_sec].n_sidedefs;
// 	i = gd->cur_sec;
// 	n_sidedef = gd->sector[i].n_sidedefs;
// 	while (i < gd->sc_len)
// 	{
// 		gd->sector[i] = gd->sector[i + 1];
// 		gd->sector[i].i_sidedefs -= n_sidedef;
// 		i++;
// 	}
// 	if (gd->cur_sec == gd->sc_len)
// 		gd->cur_sec--;
// 	gd->sc_len--;
// 	gd->cur_sd = gd->sector[gd->cur_sec].i_sidedefs - 1;
// }

// static t_sector		*cpy_sector(t_doom *doom, t_sector *sector, int *s_size)
// {
// 	t_sector	*new;
// 	int			i;

// 	new = (t_sector*)malloc(sizeof(t_sector) * *s_size * 2);
// 	if (new == NULL)
// 		doom_exit_failure(doom, "error: game design copy sector");
// 	i = 0;
// 	while (i < *s_size)
// 	{
// 		new[i] = sector[i];
// 		i++;
// 	}
// 	free(sector);
// 	*s_size *= 2;
// 	return (new);
// }

// void				add_sector(t_doom *doom)
// {
// 	if (doom->game_design.sc_len + 1 == doom->game_design.s_size)
// 		doom->game_design.sector = cpy_sector(doom, doom->game_design.sector,\
// 			&doom->game_design.s_size);
// 	doom->game_design.sc_len++;
// 	doom->game_design.sector[doom->game_design.sc_len].slope_floor = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].slope_floor_id = -1;
// 	doom->game_design.sector[doom->game_design.sc_len].slope_ceiling = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].height_ceiling = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].height_floor = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].txt_floor = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].txt_ceiling = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].i_sidedefs = \
// 	doom->game_design.w_len;
// 	doom->game_design.sector[doom->game_design.sc_len].n_sidedefs = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].i_objects = \
// 	doom->game_design.o_len;
// 	doom->game_design.sector[doom->game_design.sc_len].n_objects = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].diff_x = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].diff_y = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].action = 0;
// 	doom->game_design.sector[doom->game_design.sc_len].light_level = 10;
// }
