#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void	add_player(t_doom *doom, int x, int y)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	if (check_sector_in_sector(doom, pos) == TRUE)
	{
		doom->i_sector = doom->game_design.cur_sector;
		doom->pos = pos;
		doom->game_design.place_checkout = TRUE;
		doom->game_design.edit_sector = FALSE;
		doom->game_design.spr_tex = 6;
	}
}
