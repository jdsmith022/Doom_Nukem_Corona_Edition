#include "../../includes/doom.h"
#include "sprites.h"
#include "game_editor.h"

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
	while (i <= doom->game_design.o_len)
	{
		doom->game_design.sector[i].i_objects++;
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_objects++;
}

void		add_obj_lines(int x, int y, t_gamedesign gd, t_line **ln)
{
	ln[0][0].start.x = x + LS[gd.cur_tex].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][0].end.x = x + LS[gd.cur_tex].start_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][0].start.y = y + LS[gd.cur_tex].start_y + \
		gd.sector[gd.cur_sec].diff_y;
	ln[0][0].end.y = y + LS[gd.cur_tex].end_y + gd.sector[gd.cur_sec].diff_y;
	ln[0][1].start.x = x + LS[gd.cur_tex].end_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][1].end.x = x + LS[gd.cur_tex].end_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][1].start.y = y + LS[gd.cur_tex].start_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][1].end.y = y + LS[gd.cur_tex].end_y + gd.sector[gd.cur_sec].diff_y;
	ln[0][2].start.x = x + LS[gd.cur_tex].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][2].end.x = x + LS[gd.cur_tex].end_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][2].start.y = y + LS[gd.cur_tex].start_y +\
		gd.sector[gd.cur_sec].diff_y;
	ln[0][2].end.y = y + LS[gd.cur_tex].start_y + gd.sector[gd.cur_sec].diff_y;
	ln[0][3].start.x = x + LS[gd.cur_tex].start_x +\
		gd.sector[gd.cur_sec].diff_x;
	ln[0][3].end.x = x + LS[gd.cur_tex].end_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][3].start.y = y + LS[gd.cur_tex].end_y + gd.sector[gd.cur_sec].diff_y;
	ln[0][3].end.y = y + LS[gd.cur_tex].end_y + gd.sector[gd.cur_sec].diff_y;
}

void		add_specifications(t_gamedesign *gd, int index)
{
	gd->object[index].index = LS[gd->cur_tex].index;
	gd->object[index].amount = 4;
	gd->object[index].size = LS[gd->cur_tex].size;
	gd->object[index].textures[0] = LS[gd->cur_tex].tex1;
	gd->object[index].textures[1] = LS[gd->cur_tex].tex2;
	gd->object[index].textures[2] = LS[gd->cur_tex].tex3;
	gd->object[index].textures[3] = LS[gd->cur_tex].tex4;
	gd->object[index].block = LS[gd->cur_tex].block;
	gd->object[index].sector = gd->cur_sec;
	gd->object[index].visible = -1;
	gd->object[index].action = LS[gd->cur_tex].action;
}
