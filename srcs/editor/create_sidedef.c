/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sidedef.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 22:21:03 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

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
	doom->game_design.ed_sidedef->line = line;
	doom->game_design.ed_sidedef->previous = prev;
	doom->game_design.ed_sidedef->id = id;
	doom->game_design.ed_sidedef->opp_sector = -1;
	doom->game_design.ed_sidedef->texture = \
		doom->game_design.sd_tex_index[doom->game_design.tex_index];
	doom->game_design.ed_sidedef->sector = doom->game_design.sc_len;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.sd_len++;
}

static void		set_sidef_line(t_doom *doom, int x, int y)
{
	doom->game_design.ed_sidedef->texture = \
			doom->game_design.sd_tex_index[doom->game_design.tex_index];
	doom->game_design.draw_line.end.x = x;
	doom->game_design.draw_line.end.y = y;
	if (snap_close_sector(doom, doom->game_design.start_sector, \
	&doom->game_design.draw_line.end) == TRUE)
	{
		doom->game_design.edit_sector = TRUE;
		set_ed_sidedef_values(doom, doom->game_design.draw_line);
		set_ed_sector_values(doom);
	}
	else
		set_ed_sidedef_values(doom, doom->game_design.draw_line);
	doom->game_design.draw_line.start = doom->game_design.draw_line.end;
	doom->game_design.draw_line.end.x = -1;
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
