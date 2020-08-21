#include "../../includes/doom.h"
#include "../../includes/action.h"

void		create_mv_sidedef(t_doom *doom, t_sidedef **sidedef, int k, int len)
{
	t_sidedef	*new_sidedef;
	int			i;

	new_sidedef = (t_sidedef*)malloc(sizeof(t_sidedef) * (len + 1));
	if (new_sidedef == NULL)
		doom_exit_failure(doom, "error: creating mv sidedef");
	i = 0;
	while (i <= k)
	{
		new_sidedef[i] = sidedef[0][i];
		i++;
	}
	new_sidedef[i] = sidedef[0][i - 1];
	new_sidedef[i].line.start.x = sidedef[0][i - 1].line.start.x;
	new_sidedef[i].line.start.y = sidedef[0][i - 1].line.start.y;
	new_sidedef[i].line.end.x = sidedef[0][i - 1].line.start.x;
	new_sidedef[i].line.end.y = sidedef[0][i - 1].line.start.y;
	new_sidedef[i].opp_sector = sidedef[0][i - 1].opp_sector;
	// new_sidedef[i].opp_sidedef = sidedef[0][i - 1].opp_sidedef;
	new_sidedef[i].action = 0;
	new_sidedef[i - 1].opp_sector = -1;
	// new_sidedef[i - 1].opp_sidedef = -1;
	// new_sidedef[i - 1].action = 0;
	// new_sidedef->opp_sector = sidedef[k]->opp_sector;
	free(*sidedef);
	*sidedef = new_sidedef;
	printf("sidedef move id: %d ----\n", sidedef[0][i].opp_sector);
}

static void		init_door(t_doom *doom, int *len, int **mv_sd,
					int sd_index)
{
	int space;
	int i;
	int *new_mv_sd;

	if (!*mv_sd)
	{
		*len = 1;
		*mv_sd = (int*)malloc(sizeof(int) * *len);
		if (*mv_sd == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		mv_sd[0][0] = sd_index;
		return ;
	}
	i = 0;
	space = -1;
	while (i < *len)
	{
		if (mv_sd[0][i] == sd_index)
			return ;
		if (mv_sd[0][i] == -1)
			space = i;
		i++;
	}
	if (space != -1)
		mv_sd[0][space] = sd_index;
	else
	{
		*len *= 2;
		new_mv_sd = (int*)malloc(sizeof(int) * *len);
		if (new_mv_sd == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		while (i < *len / 2)
		{
			new_mv_sd[i] = mv_sd[0][i];
			i++;
		}
		new_mv_sd[i] = sd_index;
		i++;
		while (i < *len)
		{
			new_mv_sd[i] = -1;
			i++;
		}
	}
}

static void		calc_mv(t_sidedef *mv_sd, t_sidedef *mv_portal, int open)
{
	int x_dif;
	int y_dif;
	int x_steps;
	int y_steps;

	x_dif = mv_sd->line.end.x - mv_sd->line.start.x;
	y_dif = mv_sd->line.end.y - mv_sd->line.start.y;
	x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
	if (open)
	{
		mv_sd->line.start.x += x_steps;
		mv_sd->line.start.y += y_steps;
		mv_portal->line.end.x += x_steps;
		mv_portal->line.end.y += y_steps;
	}
}

void		sliding_door(t_doom *doom, int sd_index_add)
{
	static int	*mv_sd;
	static int	len;
	int			i;

	if (sd_index_add != -1)
	{
		// printf("init\n");
		init_door(doom, &len, &mv_sd, sd_index_add);
	}
	else
	{
		i = 0;
		while (i < len)
		{
			// printf("in while\n");
			if (mv_sd[i] != -1)
			{
				calc_mv(&doom->lib.sidedef[mv_sd[i]],\
					&doom->lib.sidedef[mv_sd[i] + 1], 1);
				if ((int)doom->lib.sidedef[mv_sd[i]].line.end.x ==\
				(int)doom->lib.sidedef[mv_sd[i]].line.start.x && \
				(int)doom->lib.sidedef[mv_sd[i]].line.end.y == \
				(int)doom->lib.sidedef[mv_sd[i]].line.start.y)
				{
					mv_sd[i] = -1;
					// printf("iff is true\n");
				}
			}
			i++;
		}
	}
}
