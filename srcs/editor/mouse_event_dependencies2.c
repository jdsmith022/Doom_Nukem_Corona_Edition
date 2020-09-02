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

