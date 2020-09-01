#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void	add_player(t_doom *doom, int x, int y)
{
	doom->game_design.pl_x = x;
	doom->game_design.pl_y = y;
	doom->game_design.pl_sec = doom->game_design.cur_sec;
	doom->game_design.pl_pos = 0;
}

void	change_sector(t_doom *doom, int change)
{
	if (doom->game_design.cur_sec + change <= doom->game_design.s_len &&
		doom->game_design.cur_sec + change >= 0)
	{
		doom->game_design.cur_sec += change;
		doom->game_design.cur_sd = \
		doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
	}
}
