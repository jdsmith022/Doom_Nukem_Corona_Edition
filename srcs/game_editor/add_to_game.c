#include "../../includes/doom.h"
#include "game_editor.h"

void    add_to_game(t_doom *doom)
{
    	for (int x = 0; x <= doom->game_design.w_len; x++)
			printf("%i %f %f %f %f\n", x, doom->game_design.sidedef[x].line.start.x, doom->game_design.sidedef[x].line.start.y, doom->game_design.sidedef[x].line.end.x, doom->game_design.sidedef[x].line.end.y);
		if (doom->game_design.sector != NULL && doom->game_design.sidedef != NULL)
        {
            doom->lib.sector = doom->game_design.sector; // free og
		    doom->lib.sidedef = doom->game_design.sidedef; //free og
		    doom->pos.x = doom->game_design.pl_x;
		    doom->pos.y = doom->game_design.pl_y;
		    doom->i_sector = doom->game_design.pl_sec;
        }
}