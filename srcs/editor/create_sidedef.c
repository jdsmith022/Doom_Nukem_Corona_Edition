#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void			set_ed_sidedef_values(t_doom *doom, t_line line)
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
	doom->game_design.ed_sidedef->texture = \
		doom->game_design.sd_tex_index[doom->game_design.tex_index];
	doom->game_design.ed_sidedef->sector = doom->game_design.sc_len;
	doom->game_design.ed_sidedef->line = line;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.sd_len++;
}

void			delete_sidedef(t_doom *doom)
{
	t_ed_sidedef *sidedef;
	t_ed_sidedef *previous;

	sidedef = doom->game_design.ed_sidedef;
	if (sidedef->sector == doom->game_design.sc_len && \
	doom->game_design.sd_len > 1 && sidedef->opp_sector == -1)
	{
		previous = sidedef->previous;
		previous->next = NULL;
		ft_bzero(sidedef, sizeof(sidedef));
		free(sidedef);
		doom->game_design.draw_line.start = previous->line.end;
		doom->game_design.sd_len--;
		doom->game_design.draw_line.end.x = -1;
		doom->game_design.draw_line.end.y = -1;
		doom->game_design.ed_sidedef = previous;
	}
	if (sidedef->opp_sector != -1)
		doom->game_design.open_connection = TRUE;
}

static bool		snap_close_sector(t_point start, t_point *end)
{
	double		distance;

	distance = point_distance(start, *end);
	if (distance < 10)
	{
		*end = start;
		return (TRUE);
	}
	return (FALSE);
}

static void		set_sidef_line(t_doom *doom, int x, int y)
{
	t_gamedesign *editor;

	editor = &doom->game_design;
	doom->game_design.ed_sidedef->texture = \
			doom->game_design.sd_tex_index[doom->game_design.tex_index];
	editor->draw_line.end.x = x;
	editor->draw_line.end.y = y;
	if (snap_close_sector(editor->start_sector, \
	&editor->draw_line.end) == TRUE)
	{
		editor->edit_sector = TRUE;
		set_ed_sidedef_values(doom, editor->draw_line);
		set_ed_sector_values(doom);
	}
	else
		set_ed_sidedef_values(doom, editor->draw_line);
	editor->draw_line.start = editor->draw_line.end;
	editor->draw_line.end.x = -1;
	editor->draw_line.end.y = -1;
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
	else if (editor->draw_line.end.x == -1 && \
	line_intersect(doom, editor->draw_line.start, x, y) == FALSE)
		set_sidef_line(doom, x, y);
}
