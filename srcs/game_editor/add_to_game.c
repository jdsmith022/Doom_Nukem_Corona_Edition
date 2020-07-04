#include "../../includes/doom.h"
#include "game_editor.h"


void	box_in_sectors(t_doom *doom)
{
	int i;
	int j;
	int save_x;
	int save_y;
	t_line diff;

	i = 0;
	diff.start.x = 0;
	diff.start.y = 0;
	diff.end.x = INFINITY;
	diff.end.y = INFINITY;
	j = 0;
	while(j < doom->game_design.w_len)
	{
		if (doom->game_design.sidedef[j].line.start.x > diff.start.x)
			diff.start.x = doom->game_design.sidedef[j].line.start.x;
		if (doom->game_design.sidedef[j].line.end.x > diff.start.x)
			diff.start.x = doom->game_design.sidedef[j].line.end.x;
		if (doom->game_design.sidedef[j].line.start.x < diff.end.x)
			diff.end.x = doom->game_design.sidedef[j].line.start.x;
		if (doom->game_design.sidedef[j].line.end.x < diff.end.x)
			diff.end.x = doom->game_design.sidedef[j].line.end.x;
		if (doom->game_design.sidedef[j].line.start.y > diff.start.y)
			diff.start.y = doom->game_design.sidedef[j].line.start.y;
		if (doom->game_design.sidedef[j].line.end.y > diff.start.y)
			diff.start.y = doom->game_design.sidedef[j].line.end.y;
		if (doom->game_design.sidedef[j].line.start.y < diff.end.y)
			diff.end.y = doom->game_design.sidedef[j].line.start.y;
		if (doom->game_design.sidedef[j].line.end.y < diff.end.y)
			diff.end.y = doom->game_design.sidedef[j].line.end.y;
		j++;
	}
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.cur_sec = i;
		save_x = doom->game_design.sector[i].diff_x;
		save_y = doom->game_design.sector[i].diff_y;
		doom->game_design.sector[i].diff_x = 0;
		doom->game_design.sector[i].diff_y = 0;
		add_sidedef(doom, diff.start.x, diff.start.y);
		add_sidedef(doom, diff.end.x, diff.start.y);
		add_sidedef(doom, diff.start.x, diff.start.y);
		add_sidedef(doom, diff.start.x, diff.end.y);
		add_sidedef(doom, diff.end.x, diff.start.y);
		add_sidedef(doom, diff.end.x, diff.end.y);
		add_sidedef(doom, diff.end.x, diff.end.y);
		add_sidedef(doom, diff.start.x, diff.end.y);
		doom->game_design.sector[i].diff_x = save_x;
		doom->game_design.sector[i].diff_y = save_y;
		i++;
	}
}

void    add_to_game(t_doom *doom)
{
    	// for (int x = 0; x <= doom->game_design.w_len; x++)
		// 	printf("%i %f %f %f %f\n", x, doom->game_design.sidedef[x].line.start.x, doom->game_design.sidedef[x].line.start.y, doom->game_design.sidedef[x].line.end.x, doom->game_design.sidedef[x].line.end.y);
		if (doom->game_design.sector != NULL && doom->game_design.w_len > 2)
        {
			printf("hello\n");
			// coor_pos(doom);
			box_in_sectors(doom);
            doom->lib.sector = doom->game_design.sector; // free og
		    doom->lib.sidedef = doom->game_design.sidedef; //free og
		    doom->pos.x = doom->game_design.pl_x;
		    doom->pos.y = doom->game_design.pl_y;
		    doom->i_sector = doom->game_design.pl_sec;
        }
}