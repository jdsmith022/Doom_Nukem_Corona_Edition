#include "../../includes/doom.h"
#include "game_editor.h"

void    add_to_line(t_line *line, double x, double y)
{
    line->start.x += fabs(x);
	line->end.x += fabs(x);
	line->start.y += fabs(y);
	line->end.y += fabs(y);
}

void	change_pos(double x, double y, t_doom *doom)
{
	int i;
	int j;
	int k;
	int side;

	i = 0;
	j = 0;
	k = 0;
	while (i <= EDIT.s_len)
	{
		SECTOR[i].diff_x += fabs(x);
		SECTOR[i].diff_y += fabs(y);
		while (j < SECTOR[i].i_sidedefs \
		+ SECTOR[i].n_sidedefs)
		{
            add_to_line(&SIDEDEF[j].line, x, y);
			j++;
		}
		while (k < SECTOR[i].i_objects \
		+ SECTOR[i].n_objects)
		{
			side = 0;
			while (side < 4)
			{
				add_to_line(&OBJECT[k].lines[side], x, y);
				side++;
			}
            OBJECT[k].pos.x += fabs(x);
            OBJECT[k].pos.y += fabs(y);
			k++;
		}
		i++;
	}
    EDIT.pl_x += fabs(x);
    EDIT.pl_y += fabs(y);
}

void    check_line(t_line line, double *x, double *y)
{
	if (line.start.x < *x)
		*x = line.start.x;
	if (line.end.x < *x)
		*x = line.end.x;
	if (line.start.y < *y)
		*y = line.start.y;
	if (line.end.y < *y)
		*y = line.end.y;
}

void	coor_pos(t_doom *doom)
{
	int		i;
	double	x;
	double	y;
	int		side;

	i = 0;
	x = 0.0;
	y = 0.0;
	while (i < EDIT.w_len)
	{
        check_line(SIDEDEF[i].line, &x, &y);
		i++;
	}
	i = 0;
	while (i < EDIT.o_len)
	{
		side = 0;
		while (side < 4)
		{
            check_line(OBJECT[i].lines[side], &x, &y);
			side++;
		}
		i++;
	}
	if (x < 0.0 || y < 0.0)
		change_pos(x, y, doom);
}
