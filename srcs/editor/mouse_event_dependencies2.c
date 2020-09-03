#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void	add_player(t_doom *doom, int x, int y)
{
	t_line	line;

	line.end.x = x;
	line.end.y = y;
	if (check_sector_in_sector(doom, line) == TRUE)
	{
		doom->game_design.pl_x = x;
		doom->game_design.pl_y = y;
		doom->game_design.player_placed = TRUE;
	}
	doom->game_design.pl_pos = 0;
}
