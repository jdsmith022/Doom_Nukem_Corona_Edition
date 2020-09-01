#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void			del_sidedef(t_doom *doom)
{
	int i;

	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef != -1)
	{
		doom->game_design.sidedef[doom->game_design.sidedef\
		[doom->game_design.cur_sd].opp_sidedef].opp_sidedef = -1;
		doom->game_design.sidedef[doom->game_design.sidedef\
		[doom->game_design.cur_sd].opp_sidedef].opp_sector = -1;
	}
	i = doom->game_design.cur_sec + 1;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_sidedefs--;
		i++;
	}
	i = doom->game_design.cur_sd;
	while (i < doom->game_design.w_len - 1)
	{
		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + 1];
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs--;
	doom->game_design.w_len--;
	doom->game_design.cur_sd--;
}

static void		sidedef_init(t_doom *doom, t_line line, int id)
{
	t_ed_sidedef *sidedef;

	while (doom->game_design.ed_sidedef->next != NULL)
		doom->game_design.ed_sidedef = doom->game_design.ed_sidedef->next;
	doom->game_design.ed_sidedef = ft_memalloc(sizeof(t_ed_sidedef) * 1);
	if (!doom->game_design.ed_sidedef)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	sidedef = doom->game_design.ed_sidedef;
	sidedef->id = id;
	sidedef->opp_sidedef = -1;
	sidedef->texture = doom->game_design.cur_tex;
	sidedef->sector = doom->game_design.cur_sec;
	sidedef->line = line;
	sidedef->next = NULL;
}

static bool			snap_close_sector(t_point start, t_point *end)
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

void			add_sidedef(t_doom *doom, int x, int y)
{
	static t_line	line;
	static t_point	start_sector;
	static int		id;
	int				i;

	if (line.start.x == -1)
	{
		line.start.x = x;
		line.start.y = y;
		start_sector = line.start;
		doom->game_design.finish_sector = FALSE;
	}
	else if (line.end.x == -1)
	{
		line.end.x = x;
		line.end.y = y;
		if (snap_close_sector(start_sector, &line.end) == TRUE)
			doom->game_design.finish_sector = TRUE;
		else
			line.end = line.start;
		sidedef_init(doom, line, id);
	}
}
