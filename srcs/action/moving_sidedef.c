#include "../../includes/doom.h"
#include "../../includes/action.h"

void		create_mv_sidedef(t_doom *doom, t_sidedef *sidedef, int i, int len)
{
	printf("in create mv_sidedef: id = %d\n", i);
	sidedef[i + 1].line.start.x = -1;
	sidedef[i + 1].line.start.y = -1;
	sidedef[i + 1].line.end.x = -1;
	sidedef[i + 1].line.end.y = -1;
	sidedef[i + 1].opp_sector = sidedef[i].opp_sector;
	sidedef[i].opp_sector = -1;
	sidedef[i + 1].action = 0;
}

void	render_sliding_door(t_doom *doom, t_sidedef *sidedef)
{
	t_point		door_start;
	double		line_angle;

	line_angle = sidedef->angle;
	door_start = sidedef->line.start;
	doom->lib.sidedef[sidedef->id + 1].line.end.x = sidedef->line.start.x + 1 * cos(line_angle);
	doom->lib.sidedef[sidedef->id + 1].line.end.y = sidedef->line.start.y + 1 * sin(line_angle);
	ft_memmove(&sidedef->line.start.x, &doom->lib.sidedef[sidedef->id + 1].line.end.x, sizeof(double));
	ft_memmove(&sidedef->line.start.y, &doom->lib.sidedef[sidedef->id + 1].line.end.y, sizeof(double));
	printf("sidedef: %f -- %f --%d   portal: %f -- %f --- %d\n", sidedef->line.start.x, sidedef->line.start.y, sidedef->id, doom->lib.sidedef[sidedef->id + 1].line.end.x, doom->lib.sidedef[sidedef->id + 1].line.end.y, doom->lib.sidedef[sidedef->id + 1].id);
	if (sidedef->line.end.x == doom->lib.sidedef[sidedef->id + 1].line.end.x && sidedef->line.end.y == doom->lib.sidedef[sidedef->id + 1].line.end.y)
	{
		doom->own_event.sliding_door = -1;
		sidedef->line.start.x = -1;
		sidedef->line.start.y = -1;
		sidedef->line.end.x = -1;
		sidedef->line.end.y = -1;
	}
	// printf("portal line: %f -- %f, %f -- %f\n",portal->line.start.x, portal->line.start.y, portal->line.end.x, portal->line.end.y);
	// printf("door line: %f -- %f, %f -- %f\n", sidedef->line.start.x, sidedef->line.start.y, sidedef->line.end.x, sidedef->line.end.y);
}

void	init_sliding_door(t_doom *doom, t_sidedef *sidedef)
{
	doom->lib.sidedef[sidedef->id + 1].opp_sector = sidedef->opp_sector;
	sidedef->opp_sector = -1;
	doom->lib.sidedef[sidedef->id + 1].action = 0;
	doom->lib.sidedef[sidedef->id + 1].line.start = sidedef->line.start;
	doom->lib.sidedef[sidedef->id + 1].line.end = sidedef->line.start;
	sidedef->angle = get_line_angle(sidedef->line);
	doom->own_event.sliding_door = sidedef->id;
}















// static void		init_door(t_doom *doom, int *len, int **mv_sd,
// 					int sd_index)
// {
// 	int space;
// 	int i;
// 	int *mv_sdf;

// 	printf("init door: len = %d\n", *len);
// 	if (!*mv_sd)
// 	{
// 		printf("static int array is not initialized\n");
// 		*len = 1;
// 		*mv_sd = (int*)malloc(sizeof(int) * *len);
// 		if (*mv_sd == NULL)
// 			doom_exit_failure(doom, MALLOC_ERR);
// 		mv_sd[0][0] = sd_index;
// 		return ;
// 	}
// 	i = 0;
// 	space = -1;
// 	while (i < *len)
// 	{
// 		if (mv_sd[0][i] == sd_index)
// 			return ;
// 		if (mv_sd[0][i] == -1)
// 			space = i;
// 		printf("after init static int array: i = %d\n", i);
// 		i++;
// 	}
// 	if (space != -1)
// 	{
// 		mv_sd[0][space] = sd_index;
// 		printf("space != -1: space = %d\n", space);
// 	}
// 	else
// 	{
// 		*len *= 2;
// 		mv_sdf = (int*)malloc(sizeof(int) * *len);
// 		if (mv_sdf == NULL)
// 			doom_exit_failure(doom, MALLOC_ERR);
// 		while (i < *len / 2)
// 		{
// 			mv_sdf[i] = mv_sd[0][i];
// 			i++;
// 		}
// 		mv_sdf[i] = sd_index;
// 		i++;
// 		while (i < *len)
// 		{
// 			mv_sdf[i] = -1;
// 			i++;
// 		}
// 	}
// }

// static void		calc_mv(t_sidedef *mv_sd, t_sidedef *mv_portal, int open)
// {
// 	int x_dif;
// 	int y_dif;
// 	int x_steps;
// 	int y_steps;

// 	x_dif = mv_sd->line.end.x - mv_sd->line.start.x;
// 	y_dif = mv_sd->line.end.y - mv_sd->line.start.y;
// 	x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
// 	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
// 	printf("dooing some movee stuff\n");
// 	if (open)
// 	{
// 		mv_sd->line.start.x += x_steps;
// 		mv_sd->line.start.y += y_steps;
// 		mv_portal->line.end.x += x_steps;
// 		mv_portal->line.end.y += y_steps;
// 	}
// }

// void		sliding_door(t_doom *doom, int sd_index_add)
// {
// 	static int	*mv_sd;
// 	static int	len;
// 	int			i;

// 	if (sd_index_add != -1)
// 	{
// 		printf("init door\n");
// 		init_door(doom, &len, &mv_sd, sd_index_add);
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (i < len)
// 		{
// 			// printf("in while\n");
// 			if (mv_sd[i] != -1)
// 			{
// 				calc_mv(&doom->lib.sidedef[mv_sd[i]],\
// 					&doom->lib.sidedef[mv_sd[i] + 1], 1);
// 				if ((int)doom->lib.sidedef[mv_sd[i]].line.end.x ==\
// 				(int)doom->lib.sidedef[mv_sd[i]].line.start.x && \
// 				(int)doom->lib.sidedef[mv_sd[i]].line.end.y == \
// 				(int)doom->lib.sidedef[mv_sd[i]].line.start.y)
// 				{
// 					mv_sd[i] = -1;
// 					doom->lib.sidedef[mv_sd[i]].opp_sector = -1;
// 					doom->lib.sidedef[sd_index_add].action = 0;
// 					doom->lib.sidedef[sd_index_add].txt_1 = 0;
// 					doom->lib.sidedef[sd_index_add].txt_2 = 0;
// 					doom->lib.sidedef[sd_index_add].txt_3 = 0;
// 					doom->lib.sidedef[sd_index_add].opp_sector = 1;
// 					printf("iff is true\n");
// 				}
// 			}
// 			i++;
// 		}
// 	}
// }
