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

static void		set_sector_values(t_doom *doom)
{
	t_ed_sector *head;
	int			id;

	id = doom->game_design.sc_len;
	head = doom->game_design.ed_sector;
	while (doom->game_design.ed_sector->next != NULL)
		doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->next = ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector->next)
		doom_exit_failure(doom, "error: malloc sector in editor\n");
	doom
}

static void		set_sidedef_values(t_doom *doom, t_line line)
{
	t_ed_sidedef *head;
	int				id;

	id = doom->game_design.sd_len;
	head = doom->game_design.ed_sidedef;
	while (doom->game_design.ed_sidedef->next != NULL)
		doom->game_design.ed_sidedef = doom->game_design.ed_sidedef->next;
	doom->game_design.ed_sidedef->next = ft_memalloc(sizeof(t_ed_sidedef));
	if (!doom->game_design.ed_sidedef->next)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	doom->game_design.ed_sidedef = doom->game_design.ed_sidedef->next;
	doom->game_design.ed_sidedef->id = id;
	doom->game_design.ed_sidedef->opp_sector = -1;
	doom->game_design.ed_sidedef->texture = doom->game_design.cur_tex;
	doom->game_design.ed_sidedef->sector = doom->game_design.cur_sec;
	doom->game_design.ed_sidedef->line = line;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.ed_sidedef = head;
	doom->game_design.cur_sd = id;
	printf("---> id = %d\n", id);
	doom->game_design.sd_len++;
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
	static t_point	start_sector;
	t_line			line;

	if (doom->game_design.draw_line.start.x == -1)
	{
		doom->game_design.draw_line.start.x = x;
		doom->game_design.draw_line.start.y = y;
		start_sector = doom->game_design.draw_line.start;
	}
	else if (doom->game_design.draw_line.end.x == -1)
	{
		doom->game_design.draw_line.end.x = x;
		doom->game_design.draw_line.end.y = y;
		if (snap_close_sector(start_sector, &doom->game_design.draw_line.end) == TRUE)
		{
			line = doom->game_design.draw_line;
			doom->game_design.draw_line.start.x = -1;
			doom->game_design.draw_line.start.y = -1;
			doom->game_design.draw_line.end.x = -1;
			doom->game_design.draw_line.end.y = -1;
			set_sidedef_values(doom, line);
			set_sector_values(doom);
		}
		else
		{
			line = doom->game_design.draw_line;
			doom->game_design.draw_line.end.x = -1;
			doom->game_design.draw_line.end.y = -1;
			set_sidedef_values(doom, line);
		}
	}
}
