#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void			set_sidedef_values(t_doom *doom, t_line line)
{
	t_ed_sidedef	*prev;
	int				id;

	id = doom->game_design.sd_len;
	while (doom->game_design.ed_sidedef->next != NULL)
		doom->game_design.ed_sidedef = doom->game_design.ed_sidedef->next;
	doom->game_design.ed_sidedef->next = ft_memalloc(sizeof(t_ed_sidedef));
	if (!doom->game_design.ed_sidedef->next)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	prev = doom->game_design.ed_sidedef;
	doom->game_design.ed_sidedef = doom->game_design.ed_sidedef->next;
	doom->game_design.ed_sidedef->previous = prev;
	doom->game_design.ed_sidedef->id = id;
	doom->game_design.ed_sidedef->opp_sector = -1;
	doom->game_design.ed_sidedef->texture = doom->game_design.cur_tex;
	doom->game_design.ed_sidedef->sector = doom->game_design.cur_sec;
	doom->game_design.ed_sidedef->line = line;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.cur_sd = id;
	printf("sidedef id = %d\n", doom->game_design.ed_sidedef->id);
	doom->game_design.sd_len++;
}

static bool		line_intersect(t_doom *doom, t_point start, int x, int y)
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
		if (isnan(intersect.x) ==  FALSE && isnan(intersect.y) == FALSE)
			return (TRUE);
		sidedef = sidedef->next;
	}
	return (FALSE);
}

static void		get_connectin_sidedef(t_doom *doom, t_line line)
{
	set_sidedef_values(doom, line);
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
	if (dist_start < dist_end && line_intersect(doom, sidedef->line.start, x, y) == FALSE)
	{
		line.start = sidedef->line.start;
		doom->game_design.start_sector = sidedef->line.end;
		get_connectin_sidedef(doom, line);
	}
	else if (line_intersect(doom, sidedef->line.end, x, y) == FALSE)
	{
		line.start = sidedef->line.end;
		doom->game_design.start_sector = sidedef->line.start;
		set_sidedef_values(doom, line);
		get_connectin_sidedef(doom, line);
	}
}

void			add_sidedef(t_doom *doom, int x, int y)
{
	t_gamedesign	*editor;
	t_point			intersect;
	t_point			line_end;

	editor = &doom->game_design;
	editor->edit_sector = FALSE;
	if (editor->draw_line.start.x == -1)
	{
		editor->draw_line.start.x = x;
		editor->draw_line.start.y = y;
		editor->start_sector = editor->draw_line.start;
	}
	else if (editor->draw_line.end.x == -1 && line_intersect(doom, editor->draw_line.start, x, y) == FALSE)
	{
		editor->draw_line.end.x = x;
		editor->draw_line.end.y = y;
		if (snap_close_sector(editor->start_sector, &editor->draw_line.end) == TRUE)
		{
			editor->edit_sector = TRUE;
			set_sidedef_values(doom, editor->draw_line);
			set_sector_values(doom);
		}
		else
			set_sidedef_values(doom, editor->draw_line);
		editor->draw_line.start = editor->draw_line.end;
		editor->draw_line.end.x = -1;
		editor->draw_line.end.y = -1;
	}
}
