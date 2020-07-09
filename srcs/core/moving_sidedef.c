#include "../../includes/doom.h"

void    init_door(int *len, int **mv_sd, int sd_index)
{
    int space;
    int i;
    int *new_mv_sd;

    if (!*mv_sd)
    {
        *len = 1;
        *mv_sd = (int*)malloc(sizeof(int) * *len);
        mv_sd[0][0] = sd_index;
        return;
    }
    i = 0;
    space = -1;
    while (i < *len)
    {
        if (mv_sd[0][i] == sd_index)
            return ;
        if (mv_sd[0][i] == -1)
            space = i;
        i++;
    }
    if (space != -1)
        mv_sd[0][space]= sd_index;
    else
    {
        *len *= 2;
        new_mv_sd = (int*)malloc(sizeof(int) * *len);
        while (i < *len / 2)
        {
            new_mv_sd[i] = mv_sd[0][i];
            i++;
        }
        new_mv_sd[i] = sd_index;
        i++;
        while (i < *len)
        {
            new_mv_sd[i] = -1;
            i++;
        }
    }
}

void    calc_mv(t_sidedef *mv_sd, int open)
{
    int x_dif;
    int y_dif;
    int x_steps;
    int y_steps;

    x_dif = mv_sd->line.end.x - mv_sd->line.start.x;
    y_dif = mv_sd->line.end.y - mv_sd->line.start.y;
    x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
    if (open)
    {
        mv_sd->line.end.x -= x_steps;
        mv_sd->line.end.y -= y_steps;
    }


}

void    sliding_door(t_doom *doom, int sd_index)
{
    static int *mv_sd;
    static int  len;
    int         i;

    if (sd_index != -1)
        init_door(&len, &mv_sd, sd_index);
    else
    {
        i = 0;
        while (i < len)
        {
            if (mv_sd[i] != -1)
            {
                calc_mv(&doom->lib.sidedef[mv_sd[i]], 1);
                if ((int)doom->lib.sidedef[mv_sd[i]].line.end.x == (int)doom->lib.sidedef[mv_sd[i]].line.start.x && \
                    (int)doom->lib.sidedef[mv_sd[i]].line.end.y == (int)doom->lib.sidedef[mv_sd[i]].line.start.y)
                    mv_sd[i] = -1;
            }
            i++;
        }
    }
}