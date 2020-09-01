#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

static void		copy_lines(t_sprite *new, t_sprite **object, int *side, int i)
{
	new[i].lines[*side] = object[0][i].lines[*side];
	new[i].textures[*side] = object[0][i].textures[*side];
	*side += 1;
}

static void		cpy_object(t_doom *doom, t_sprite **object, int *o_size)
{
	t_sprite	*new;
	int			i;
	int			side;

	new = (t_sprite*)ft_memalloc(sizeof(t_sprite) * *o_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, "error: cpy object");
	i = 0;
	while (i < *o_size)
	{
		new[i] = object[0][i];
		new[i].lines = (t_line*)ft_memalloc(sizeof(t_line) * 4);
		new[i].textures = (int*)ft_memalloc(sizeof(int) * 4);
		side = 0;
		while (side < 4)
			copy_lines(new, object, &side, i);
		free(object[0][i].lines);
		free(object[0][i].textures);
		i++;
	}
	free(*object);
	*o_size *= 2;
	*object = new;
}

static void		mv_object(t_sprite **object, int o_len, int id)
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

static void		add_object_to_array(int x, int y, t_doom *doom)
{
	doom->game_design.object[doom->game_design.o_len].lines = \
		(t_line*)malloc(sizeof(t_line) * 4);
	doom->game_design.object[doom->game_design.o_len].textures = \
		(int*)malloc(sizeof(int) * 4);
	doom->game_design.object[doom->game_design.o_len].pos.x = \
		x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	doom->game_design.object[doom->game_design.o_len].pos.y = \
		y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	add_specifications(&(doom->game_design), doom->game_design.o_len);
	add_obj_lines(x, y, doom->game_design,\
	&(doom->game_design.object[doom->game_design.o_len].lines));
}

void			add_object(t_doom *doom, int x, int y)
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
