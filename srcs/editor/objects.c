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

void		cpy_ln_txt(t_sprite **new, int i, t_sprite **object)
{
	int side;

	side = 0;
	while (side < 4)
	{
		new[0][i].lines[side] = object[0][i].lines[side];
		new[0][i].textures[side] = object[0][i].textures[side];
		side++;
	}
}

void		cpy_object(t_doom *doom, t_sprite **object, int *o_size)
{
	t_sprite	*new;
	int			i;

	new = (t_sprite*)ft_memalloc(sizeof(t_sprite) * *o_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < *o_size)
	{
		new[i] = object[0][i];
		new[i].lines = (t_line*)ft_memalloc(sizeof(t_line) * 4);
		new[i].textures = (int*)ft_memalloc(sizeof(int) * 4);
		cpy_ln_txt(&new, i, object);
		free(object[0][i].lines);
		free(object[0][i].textures);
		i++;
	}
	free(*object);
	*o_size *= 2;
	*object = new;
}

void		mv_object(t_sprite **object, int o_len, int id)
{
	int			i;
	t_sprite	safe;
	t_sprite	safe2;
	int			side;

	i = id;
	safe = object[0][i];
	object[0][i] = object[0][o_len];
	i++;
	while (i < o_len)
	{
		safe2 = object[0][i];
		object[0][i] = safe;
		safe = safe2;
		i++;
	}
	object[0][i] = safe;
}

void		add_obj_lines(int x, int y, t_gamedesign gd, t_line **ln)
{
	ln[0][0].start.x = x + LS[gd.cur_tex].start_x +\
	gd.sector[gd.cur_sec].diff_x;
	ln[0][0].end.x = x + LS[gd.cur_tex].start_x + gd.sector[gd.cur_sec].diff_x;
	ln[0][0].start.y = y + LS[gd.cur_tex].start_y +\
	gd.sector[gd.cur_sec].diff_y;
	ln[0][0].end.y = y + LS[gd.cur_tex].end_y + gd.sector[gd.cur_sec].diff_y;
	ln[0][1].start.x = x + LS[gd.cur_tex].end_x +\
	gd.sector[gd.cur_sec].diff_x;
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
	ln[0][3].start.y = y + LS[gd.cur_tex].end_y +\
	gd.sector[gd.cur_sec].diff_y;
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

void	add_object_to_array(int x, int y, t_doom *doom)
{
	doom->game_design.object[doom->game_design.o_len].lines =\
	(t_line*)malloc(sizeof(t_line) * 4);
	doom->game_design.object[doom->game_design.o_len].textures =\
	(int*)malloc(sizeof(int) * 4);
	doom->game_design.object[doom->game_design.o_len].pos.x = \
		x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	doom->game_design.object[doom->game_design.o_len].pos.y = \
		y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	add_specifications(&(doom->game_design), doom->game_design.o_len);
	add_obj_lines(x, y, doom->game_design,\
	&(doom->game_design.object[doom->game_design.o_len].lines));
}

void	add_object(t_doom *doom, int x, int y)
{
	if (doom->game_design.object == NULL)
	{
		doom->game_design.object = (t_sprite*)malloc(sizeof(t_sprite) * 2);
		doom->game_design.o_size = 2;
		doom->game_design.o_len = 0;
	}
	if (doom->game_design.o_size < doom->game_design.o_len + 1)
		cpy_object(doom, &(doom->game_design.object),\
		&doom->game_design.o_size);
	add_object_to_array(x, y, doom);
	if (doom->game_design.cur_sec != doom->game_design.s_len)
		mv_object(&doom->game_design.object, doom->game_design.o_len, \
		doom->game_design.sector[doom->game_design.cur_sec].i_objects);
	correct_i_object(doom->game_design.cur_sec + 1, doom);
	doom->game_design.cur_obj = doom->game_design.cur_sec != \
		doom->game_design.s_len ? \
		doom->game_design.sector[doom->game_design.cur_sec].i_objects \
		: doom->game_design.o_len;
	doom->game_design.o_len++;
}
