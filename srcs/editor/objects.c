#include "../../includes/doom.h"
#include "sprites.h"
#include "game_editor.h"

void		del_obj(t_doom *doom)
{
	int i;

	i = EDIT.cur_sec + 1;
	while (i <= EDIT.s_len)
	{
		SECTOR[i].i_objects--;
		i++;
	}
	i = EDIT.cur_obj;
	while (i < EDIT.o_len - 1)
	{
		OBJECT[i] = OBJECT[i + 1];
		i++;
	}
	SECTOR[EDIT.cur_sec].n_objects--;
	EDIT.o_len--;
	EDIT.cur_obj--;
}

void        correct_i_object(int i, t_doom *doom)
{
	while (i <= EDIT.o_len)
	{
		SECTOR[i].i_objects++;
		i++;
	}
	SECTOR[EDIT.cur_sec].n_objects++;

}

t_sprite *cpy_object(t_doom *doom, t_sprite *object, int *o_size)
{
	t_sprite	*new;
	int			i;

	new = (t_sprite*)malloc(sizeof(t_sprite) * *o_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, "error: cpy object");
	i = 0;
	while (i < *o_size)
	{
		new[i] = object[i];
		i++;
	}
	free(object);
	*o_size *= 2;
	while (i < *o_size)
	{
		new[i].lines = (t_line*)malloc(sizeof(t_line) * 4);
		new[i].textures = (int*)malloc(sizeof(int) * 4);
		if (new[i].lines == NULL || new[i].textures == NULL)
			doom_exit_failure(doom, "error: cpy object");
		i++;
	}
	return (new);
}

void		mv_object(t_sprite **object, int o_len, int id)
{
	int			i;
	t_sprite	safe;
	t_sprite	safe2;

	i = id;
	safe = object[0][i];
	object[0][i] = object[0][o_len];
	i++;
	while (i < o_len)
	{
		safe2 = object[0][o_len];
		object[0][i] = safe;
		safe = safe2;
		i++;
	}
	object[0][i] = safe;
}

void	add_obj_lines(int x, int y, t_doom *doom, int index)
{
    OBJECT[index].lines[0].start.x = x + LEVEL_SPRITES[EDIT.cur_tex].start_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[0].end.x = x + LEVEL_SPRITES[EDIT.cur_tex].start_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[0].start.y = y + LEVEL_SPRITES[EDIT.cur_tex].start_y + SECTOR[EDIT.cur_sec].diff_y;
    OBJECT[index].lines[0].end.y = y + LEVEL_SPRITES[EDIT.cur_tex].end_y + SECTOR[EDIT.cur_sec].diff_y;
	OBJECT[index].lines[1].start.x = x + LEVEL_SPRITES[EDIT.cur_tex].end_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[1].end.x = x + LEVEL_SPRITES[EDIT.cur_tex].end_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[1].start.y = y + LEVEL_SPRITES[EDIT.cur_tex].start_y + SECTOR[EDIT.cur_sec].diff_y;
    OBJECT[index].lines[1].end.y = y + LEVEL_SPRITES[EDIT.cur_tex].end_y + SECTOR[EDIT.cur_sec].diff_y;
	OBJECT[index].lines[2].start.x = x + LEVEL_SPRITES[EDIT.cur_tex].start_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[2].end.x = x + LEVEL_SPRITES[EDIT.cur_tex].end_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[2].start.y = y + LEVEL_SPRITES[EDIT.cur_tex].start_y + SECTOR[EDIT.cur_sec].diff_y;
    OBJECT[index].lines[2].end.y = y + LEVEL_SPRITES[EDIT.cur_tex].start_y + SECTOR[EDIT.cur_sec].diff_y;
	OBJECT[index].lines[3].start.x = x + LEVEL_SPRITES[EDIT.cur_tex].start_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[3].end.x = x + LEVEL_SPRITES[EDIT.cur_tex].end_x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[index].lines[3].start.y = y + LEVEL_SPRITES[EDIT.cur_tex].end_y + SECTOR[EDIT.cur_sec].diff_y;
    OBJECT[index].lines[3].end.y = y + LEVEL_SPRITES[EDIT.cur_tex].end_y + SECTOR[EDIT.cur_sec].diff_y;
}

void	add_specifications(t_doom *doom, int index)
{
	OBJECT[index].index = LEVEL_SPRITES[EDIT.cur_tex].index;
    OBJECT[index].amount = 4;
  	OBJECT[index].size = LEVEL_SPRITES[EDIT.cur_tex].size;
    OBJECT[index].textures[0] = LEVEL_SPRITES[EDIT.cur_tex].tex1;
    OBJECT[index].textures[1] = LEVEL_SPRITES[EDIT.cur_tex].tex2;
    OBJECT[index].textures[2] = LEVEL_SPRITES[EDIT.cur_tex].tex3;
    OBJECT[index].textures[3] = LEVEL_SPRITES[EDIT.cur_tex].tex4;
    OBJECT[index].block = LEVEL_SPRITES[EDIT.cur_tex].block;
    OBJECT[index].sector = EDIT.cur_sec;
    OBJECT[index].visible = -1;
	OBJECT[index].action = LEVEL_SPRITES[EDIT.cur_tex].action;
}

void    add_object_to_array(int x, int y, t_doom *doom)
{
    OBJECT[EDIT.o_len].pos.x = x + SECTOR[EDIT.cur_sec].diff_x;
    OBJECT[EDIT.o_len].pos.y = y + SECTOR[EDIT.cur_sec].diff_y;
	add_specifications(doom, EDIT.o_len);
	add_obj_lines(x, y, doom, EDIT.o_len);
}


void    add_object(t_doom *doom, int x, int y)
{
    if (OBJECT == NULL)
	{
		OBJECT = (t_sprite*)malloc(sizeof(t_sprite) * 2);
		OBJECT[0].lines = (t_line*)malloc(sizeof(t_line) * 4);
		OBJECT[0].textures = (int*)malloc(sizeof(int) * 4);
		OBJECT[1].lines = (t_line*)malloc(sizeof(t_line) * 4);
		OBJECT[1].textures = (int*)malloc(sizeof(int) * 4);
		EDIT.o_size = 2;
		EDIT.o_len = 0;
	}
    if (EDIT.o_size < EDIT.o_len + 1)
			OBJECT = cpy_object(doom, OBJECT, &EDIT.o_size);
	add_object_to_array(x, y, doom);
    if (EDIT.cur_sec != EDIT.s_len)
		mv_object(&OBJECT, EDIT.o_len, \
		SECTOR[EDIT.cur_sec].i_objects);
    correct_i_object(EDIT.cur_sec + 1, doom);
    EDIT.cur_obj = EDIT.cur_sec != EDIT.s_len ? \
	SECTOR[EDIT.cur_sec].i_objects \
	: EDIT.o_len;
    EDIT.o_len++;
}