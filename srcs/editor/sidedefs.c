#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

// void			del_sidedef(t_doom *doom)
// {
// 	int i;

// 	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef != -1)
// 	{
// 		doom->game_design.sidedef[doom->game_design.sidedef\
// 		[doom->game_design.cur_sd].opp_sidedef].opp_sidedef = -1;
// 		doom->game_design.sidedef[doom->game_design.sidedef\
// 		[doom->game_design.cur_sd].opp_sidedef].opp_sector = -1;
// 	}
// 	i = doom->game_design.cur_sec + 1;
// 	while (i <= doom->game_design.sc_len)
// 	{
// 		doom->game_design.sector[i].i_sidedefs--;
// 		i++;
// 	}
// 	i = doom->game_design.cur_sd;
// 	while (i < doom->game_design.w_len - 1)
// 	{
// 		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + 1];
// 		i++;
// 	}
// 	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs--;
// 	doom->game_design.w_len--;
// 	doom->game_design.cur_sd--;
// }


static void		set_sector_sidedefs(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	int				i_sidedef;
	int				n_sidedefs;

	i_sidedef = -1;
	n_sidedefs = 0;
	sidedef = doom->game_design.ed_sidedef;
	while (sidedef->next != NULL)
	{
		sidedef = sidedef->next;
		if (i_sidedef == -1 && sidedef->sector == doom->game_design.cur_sec)
			i_sidedef = sidedef->id;
		if (sidedef->sector == doom->game_design.cur_sec)
		{
			n_sidedefs++;
			printf("%d\n", n_sidedefs);
		}
	}
	doom->game_design.ed_sector->i_sidedefs = i_sidedef;
	doom->game_design.ed_sector->n_sidedefs = n_sidedefs;
}

static void		set_sector_values(t_doom *doom)
{
	t_ed_sector *prev;
	int			id;

	id = doom->game_design.sc_len;
	while (doom->game_design.ed_sector->next != NULL)
		doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->next = ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector->next)
		doom_exit_failure(doom, "error: malloc sector in editor\n");
	prev = 	doom->game_design.ed_sector;
	doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->previous = prev;
	set_sector_sidedefs(doom);
	doom->game_design.ed_sector->height_floor = doom->game_design.floor_height;
	doom->game_design.ed_sector->height_ceiling =\
		doom->game_design.ceiling_height;
	doom->game_design.ed_sector->light_level = doom->game_design.light_level;
	doom->game_design.ed_sector->id = id;
	doom->game_design.ed_sector->next = NULL;
	doom->game_design.sc_len++;
	doom->game_design.cur_sec++;
	printf("set sector %d, %d\n", doom->game_design.ed_sector->i_sidedefs, doom->game_design.ed_sector->n_sidedefs);
}

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
	printf("---> id = %d sector = %d\n", id, doom->game_design.ed_sidedef->sector);
	doom->game_design.sd_len++;
}

void			check_connection(t_doom *doom, int x, int y)
{
	t_ed_sidedef	*sidedef;
	double			dist_end;
	double			dist_start;
	t_point			end_line;

	sidedef = doom->game_design.ed_sidedef;
	dist_start = point_distance(end_line, sidedef->line.start);
	dist_end = point_distance(end_line, sidedef->line.end);
	if (dist_start < dist_end)
		doom->game_design.draw_line.start = sidedef->line.start;
	else
		doom->game_design.draw_line.start = sidedef->line.end;
	doom->game_design.draw_line.end = end_line;
	doom->game_design.open_connection = FALSE;
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

	doom->game_design.edit_sector = FALSE;
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
			doom->game_design.edit_sector = TRUE;
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
			doom->game_design.draw_line.start = line.end;
			set_sidedef_values(doom, line);
		}
	}
}
