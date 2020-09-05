#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

bool		line_intersect(t_doom *doom, t_point start, int x, int y)
{
	t_ed_sidedef	*sidedef;
	t_line			line1;
	t_line			line2;
	t_point			intersect;

	sidedef = doom->game_design.sd_head;
	line1.start = start;
	line1.end.x = x;
	line1.end.y = y;
	while (sidedef->next != NULL)
	{
		line2 = sidedef->line;
		intersect = check_line_intersection(line1, line2);
		if (isnan(intersect.x) == FALSE && isnan(intersect.y) == FALSE)
			return (TRUE);
		sidedef = sidedef->next;
	}
	return (FALSE);
}

static void		get_connection_sidedef(t_doom *doom, t_line line)
{
	if (check_sector_in_sector(doom, line.end) == TRUE)
		return ;
	set_ed_sidedef_values(doom, line);
	doom->game_design.draw_line.start = line.end;
	doom->game_design.open_connection = FALSE;
}

void			check_connection(t_doom *doom, int x, int y)
{
	t_ed_sidedef	*sidedef;
	double			dist_end;
	double			dist_start;
	t_line			line;

	sidedef = doom->game_design.ed_sidedef;
	line.end.x = x;
	line.end.y = y;
	dist_start = point_distance(line.end, sidedef->line.start);
	dist_end = point_distance(line.end, sidedef->line.end);
	if (dist_start < dist_end && \
	line_intersect(doom, sidedef->line.start, x, y) == FALSE)
	{
		line.start = sidedef->line.start;
		doom->game_design.start_sector = sidedef->line.end;
		get_connection_sidedef(doom, line);
	}
	else if (line_intersect(doom, sidedef->line.end, x, y) == FALSE)
	{
		line.start = sidedef->line.end;
		doom->game_design.start_sector = sidedef->line.start;
		get_connection_sidedef(doom, line);
	}
}
