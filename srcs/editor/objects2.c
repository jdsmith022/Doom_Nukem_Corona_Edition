#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void		del_obj(t_doom *doom)
{
	int i;

	i = doom->game_design.cur_sec + 1;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_objects--;
		i++;
	}
	i = doom->game_design.cur_obj;
	while (i < doom->game_design.o_len - 1)
	{
		doom->game_design.object[i] = doom->game_design.object[i + 1];
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_objects--;
	doom->game_design.o_len--;
	doom->game_design.cur_obj--;
}

void		correct_i_object(int i, t_doom *doom)
{
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_objects++;
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_objects++;
}

static void	add_obj_lines2(int x, int y, t_gamedesign gd, t_line **ln)
{
	ln[0][2].start.x = x + level_sprites[gd.index_obj].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][2].end.x = x + level_sprites[gd.index_obj].end_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][2].start.y = y + level_sprites[gd.index_obj].start_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][2].end.y = y + level_sprites[gd.index_obj].start_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][3].start.x = x + level_sprites[gd.index_obj].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][3].end.x = x + level_sprites[gd.index_obj].end_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][3].start.y = y + level_sprites[gd.index_obj].end_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][3].end.y = y + level_sprites[gd.index_obj].end_y +\
		gd.sector[gd.cur_sec].diff_y;
}

void		add_obj_lines(int x, int y, t_gamedesign gd, t_line **ln)
{
	ln[0][0].start.x = x + level_sprites[gd.index_obj].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][0].end.x = x + level_sprites[gd.index_obj].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][0].start.y = y + level_sprites[gd.index_obj].start_y + \
		gd.sector[gd.cur_sec].diff_y;
	ln[0][0].end.y = y + level_sprites[gd.index_obj].end_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][1].start.x = x + level_sprites[gd.index_obj].end_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][1].end.x = x + level_sprites[gd.index_obj].end_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][1].start.y = y + level_sprites[gd.index_obj].start_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][1].end.y = y + level_sprites[gd.index_obj].end_y +\
		gd.sector[gd.cur_sec].diff_y;
	add_obj_lines2(x, y, gd, ln);
}

void		add_specifications(t_gamedesign *gd, int index)
{
	gd->object[index].index = level_sprites[gd->index_obj].index;
	gd->object[index].amount = 4;
	gd->object[index].size = level_sprites[gd->index_obj].size;
	gd->object[index].textures[0] = level_sprites[gd->index_obj].tex1;
	gd->object[index].textures[1] = level_sprites[gd->index_obj].tex2;
	gd->object[index].textures[2] = level_sprites[gd->index_obj].tex3;
	gd->object[index].textures[3] = level_sprites[gd->index_obj].tex4;
	gd->object[index].block = level_sprites[gd->index_obj].block;
	gd->object[index].sector = gd->cur_sec;
	gd->object[index].visible = -1;
	gd->object[index].action = level_sprites[gd->index_obj].action;
	printf("index = %d,	object id:	%d, level %d\n", index, level_sprites[gd->index_obj].index, gd->cur_sec);
}
