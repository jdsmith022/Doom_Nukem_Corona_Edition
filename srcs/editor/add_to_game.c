#include "../../includes/doom.h"
#include "game_editor.h"

void	change_pos(double x, double y, t_doom *doom)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].diff_x += fabs(x);
		doom->game_design.sector[i].diff_y += fabs(y);
		while (j < doom->game_design.sector[i].i_sidedefs \
		+ doom->game_design.sector[i].n_sidedefs)
		{
			doom->game_design.sidedef[j].line.start.x += fabs(x);
			doom->game_design.sidedef[j].line.end.x += fabs(x);
			doom->game_design.sidedef[j].line.start.y += fabs(y);
			doom->game_design.sidedef[j].line.end.y += fabs(y);
			j++;
		}
		i++;
	}
}

void	coor_pos(t_doom *doom)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = 0;
	x = 0.0;
	y = 0.0;
	while (i < doom->game_design.w_len)
	{
		if (doom->game_design.sidedef[i].line.start.x < x)
			x = doom->game_design.sidedef[i].line.start.x;
		if (doom->game_design.sidedef[i].line.end.x < x)
			x = doom->game_design.sidedef[i].line.end.x;
		if (doom->game_design.sidedef[i].line.start.y < y)
			y = doom->game_design.sidedef[i].line.start.y;
		if (doom->game_design.sidedef[i].line.end.y < y)
			y = doom->game_design.sidedef[i].line.end.y;
		i++;
	}
	if (x < 0.0 || y < 0.0)
		change_pos(x, y, doom);
}

t_sidedef	*new_level_sidedef(t_doom *doom, t_sidedef *sidedef, int w_len)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * w_len);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < w_len)
	{
		new[i] = sidedef[i];
		i++;
	}
	return (new);
}

t_sector	*new_level_sector(t_doom *doom, t_sector *sector, int s_len)
{
	t_sector	*new;
	int			i;

	new = (t_sector*)malloc(sizeof(t_sector) * (s_len + 1));
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i <= s_len)
	{
		new[i] = sector[i];
		i++;
	}
	return (new);
}

t_sector	*light_correction(t_sector *sector, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		if (sector[i].light_level != 0)
			sector[i].light_level /= 10.0;
		sector[i].light = TRUE;
		i++;
	}
	return (sector);
}

void		add_to_game(t_doom *doom)
{
	if (doom->game_design.sector != NULL && doom->game_design.w_len > 2)
	{
		if (doom->game_design.pl_x > 0 && doom->game_design.pl_y > 0)
		{
			coor_pos(doom);
			printf("1\n");
			box_in_sectors(doom);
			printf("2\n");
			free(doom->lib.sector); //rm when there are multiple levels		
			free(doom->lib.sidedef); //rm when there are multiple levels	
			printf("3\n");			
			doom->lib.sector = new_level_sector(doom,\
				doom->game_design.sector, doom->game_design.s_len + 1);		
			printf("4\n");			
			doom->lib.sidedef = new_level_sidedef(doom,\
				doom->game_design.sidedef, doom->game_design.w_len + 1);	
			printf("5\n");						
			doom->lib.sector = light_correction(\
				doom->lib.sector, doom->game_design.s_len);
			printf("6\n");				
			doom->pos.x = doom->game_design.pl_x;
			doom->pos.y = doom->game_design.pl_y;
			doom->i_sector = doom->game_design.pl_sec;
			doom->player_height = doom->player_height \
			+ doom->lib.sector[doom->game_design.pl_sec].height_floor;
			doom->light = TRUE;
			printf("7\n");
		}
	}
}
