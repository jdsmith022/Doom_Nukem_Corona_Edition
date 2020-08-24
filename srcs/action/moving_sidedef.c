
#include "../../includes/doom.h"
#include "../../includes/action.h"

void		render_sliding_door(t_doom *doom, t_sidedef *sidedef)
{
	t_point		door_start;
	double		line_angle;

	line_angle = sidedef->angle;
	door_start = sidedef->line.start;
	doom->lib.sidedef[sidedef->id + 1].line.end.x = \
		sidedef->line.start.x + 1 * cos(line_angle);
	doom->lib.sidedef[sidedef->id + 1].line.end.y = \
		sidedef->line.start.y + 1 * sin(line_angle);
	ft_memmove(&sidedef->line.start.x, \
		&doom->lib.sidedef[sidedef->id + 1].line.end.x, sizeof(double));
	ft_memmove(&sidedef->line.start.y, \
		&doom->lib.sidedef[sidedef->id + 1].line.end.y, sizeof(double));
	if (sidedef->line.end.x == doom->lib.sidedef[sidedef->id + 1].line.end.x \
	&& sidedef->line.end.y == doom->lib.sidedef[sidedef->id + 1].line.end.y)
	{
		doom->own_event.sliding_door = -1;
		sidedef->line.start.x = -1;
		sidedef->line.start.y = -1;
		sidedef->line.end.x = -1;
		sidedef->line.end.y = -1;
		sidedef->action = 0;
	}
}

void		init_sliding_door(t_doom *doom, t_sidedef *sidedef)
{
	doom->lib.sidedef[sidedef->id + 1].line.start = sidedef->line.start;
	doom->lib.sidedef[sidedef->id + 1].line.end = sidedef->line.start;
	sidedef->angle = get_line_angle(sidedef->line);
	doom->own_event.sliding_door = sidedef->id;
}

void		create_mv_sidedef(t_doom *doom, t_sidedef *sidedef, int i)
{
	sidedef[i].id = i;
	sidedef[i].line.start.x = -1;
	sidedef[i].line.start.y = -1;
	sidedef[i].line.end.x = -1;
	sidedef[i].line.end.y = -1;
	sidedef[i].opp_sector = sidedef[i - 1].opp_sector;
	sidedef[i - 1].opp_sector = -1;
	sidedef[i].action = 0;
	sidedef[i].sector = sidedef[i - 1].sector;
}
