#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/read.h"

static void		add_inf_to_m_obj(t_doom *doom, t_m_object *sprite,
					char *line, int i, int safe)
{
	if (i == 0)
		sprite->name = line;
	if (i == 1)
		sprite->action = safe;
	if (i == 2)
		sprite->speed = safe;
	if (i == 3)
		sprite->spawn_time = safe;
	if (i == 4)
	{
		sprite->amount = safe;
		sprite->textures = (int*)malloc(sizeof(int) * safe);
		if (sprite->textures == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
	}
	if (i > 4 && i < sprite->amount + 4)
	{
		if (i % 2 == 1)
			sprite->textures[(i - 5) / 2] = safe;
		else
			sprite->face_ang[(i - 6) / 2] = safe;
	}
}

static t_m_object	mov_object_inf(t_doom *doom, int fd, int sector)
{
	int			i;
	char		*line;
	t_m_object	m_sprite;
	int			safe;

	(void)sector;
	i = 0;
	m_sprite.amount = 0;
	while (i < 5 + m_sprite.amount)
	{
		if (i > 0)
			safe = get_line(&line, fd, \
			"moving object informations does not exist", 1);
		else
			get_line(&line, fd, "moving object name does not exist", 0);
		add_inf_to_m_obj(doom, &m_sprite, line, i, safe);
		free(line);
		i++;
	}
	return (m_sprite);
}

static void		create_object(t_doom *doom, int fd, int i,
					int total_sprites)
{
	t_lib		*col_lib;
	static int	l;
	static int	obj_int;
	int			j;

	col_lib = &doom->lib;
	if (!l)
	{
		l = 0;
		obj_int = 0;
	}
	col_lib->sector[i].i_objects = obj_int;
	j = 0;
	while (j < col_lib->sector[i].n_objects)
	{
		col_lib->sprites[l] = object_inf(fd, i, col_lib->len_obj_lib);
		l++;
		j++;
	}
	obj_int = obj_int + j;
	if (obj_int > total_sprites)
		doom_exit_failure(doom, \
			"error: number of objects in file is incorrect\n");
}

void		add_inf_to_lib(t_doom *doom, int len, int fd)
{
	int		i;
	int		j;
	char	*line;
	t_lib	*col_lib;

	col_lib = &doom->lib;
	i = 0;
	while (i < len)
	{
		create_sidedef(doom, fd, len, i);
		create_object(doom, fd, i, doom->total_sprites);
		i++;
	}
	j = 0;
	get_line(&line, fd, "the moving object number can not be read", 1);
	col_lib->n_mov_sprites = ft_atoi(line);
	free(line);
	col_lib->mov_sprites = \
		(t_m_object*)malloc(sizeof(t_m_object) * col_lib->n_mov_sprites);
	if (col_lib->mov_sprites == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	while (j < col_lib->n_mov_sprites)
	{
		col_lib->mov_sprites[j] = mov_object_inf(doom, fd, j);
		j++;
	}
}
