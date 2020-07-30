#include "../../includes/doom.h"

#include <stdio.h>

void    init_infection(t_sidedef *infection, t_doom *doom)
{
    int x;
    int y;
    int i;
    int x_diff;
    int y_diff;
    double x_steps;
    double y_steps;

    i = -1;
    while (i == -1 || doom->lib.sidedef[i].opp_sector != -1)
        i = rand() % doom->lib.len_sidedef;
    x_diff = (doom->lib.sidedef[i].line.end.x) - (doom->lib.sidedef[i].line.start.x);
	y_diff = (doom->lib.sidedef[i].line.end.y) - (doom->lib.sidedef[i].line.start.y);
	x_steps = (float)x_diff / (float)(abs(x_diff) + abs(y_diff));
	y_steps = (float)y_diff / (float)(abs(x_diff) + abs(y_diff));
    x_diff++;
    y_diff++;
    infection->line.start.x = doom->lib.sidedef[i].line.end.x > doom->lib.sidedef[i].line.start.x ? 
                                rand() % (x_diff - (int)(x_steps * 16)) + doom->lib.sidedef[i].line.start.x :
                                rand() % (x_diff - (int)(x_steps * 16)) + doom->lib.sidedef[i].line.end.x;
    infection->line.start.y = doom->lib.sidedef[i].line.end.y > doom->lib.sidedef[i].line.start.y ? 
                                rand() % (y_diff - (int)(y_steps * 16)) + doom->lib.sidedef[i].line.start.y :
                                rand() % (y_diff - (int)(y_steps * 16)) + doom->lib.sidedef[i].line.end.y;
    infection->line.end.x = infection->line.start.x + x_steps * 15.0;
    infection->line.end.y = infection->line.start.y + y_steps * 15.0;
	infection->id = 0;
	infection->sector = doom->lib.sidedef[i].sector;
	infection->opp_sidedef = -1;
	infection->opp_sector = -1;
	infection->txt_1 = 0;
    infection->txt_2 = 9; //should be put with a flag or something
	infection->txt_3 = 0;
}

void    add_infection(t_doom *doom)
{
    if (rand() % 10 == 1 && doom->lib.cur_len_infection < 100)
    {
        doom->lib.cur_len_infection++;
        init_infection(&(doom->lib.infection[doom->lib.cur_len_infection]), doom);
    }
}