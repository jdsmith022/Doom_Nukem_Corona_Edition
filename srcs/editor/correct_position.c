#include "../../includes/doom.h"
#include "game_editor.h"

static void    add_to_line(t_line *line, double x, double y)
{
    line->start.x += fabs(x);
	line->end.x += fabs(x);
	line->start.y += fabs(y);
	line->end.y += fabs(y);
}

static int change_object(t_sprite **object, int k, t_sector sector, t_point change)
{
	int side;
	
	side = 0;
	while (k < sector.i_objects + sector.n_objects)
	{
		while (side < 4)
		{
			add_to_line(&object[k]->lines[side], change.x, change.y);
			side++;
		}
		object[k]->pos.x += fabs(change.x);
		object[k]->pos.y += fabs(change.y);
		k++;
	}
	return (k);
}

static void	change_pos(t_point change, t_doom *doom)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].diff_x += fabs(change.x);
		doom->game_design.sector[i].diff_y += fabs(change.y);
		while (j < doom->game_design.sector[i].i_sidedefs \
		+ doom->game_design.sector[i].n_sidedefs)
		{
            add_to_line(&doom->game_design.sidedef[j].line, change.x, change.y);
			j++;
		}
		k = change_object(&doom->game_design.object, k,\
		doom->game_design.sector[i], change);
		i++;
	}
    doom->game_design.pl_x += fabs(change.x);
    doom->game_design.pl_y += fabs(change.y);
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
	t_point change;
	int		side;

	i = 0;
	change.x = 0.0;
	change.y = 0.0;
	while (i < doom->game_design.w_len)
	{
        check_line(doom->game_design.sidedef[i].line, &change.x, &change.y);
		i++;
	}
	i = 0;
	while (i < doom->game_design.o_len)
	{
		side = 0;
		while (side < 4)
		{
            check_line(doom->game_design.object[i].lines[side],\
			&change.x, &change.y);
			side++;
		}
		i++;
	}
	if (change.x < 0.0 || change.y < 0.0)
		change_pos(change, doom);
}
