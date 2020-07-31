#include "../../includes/doom.h"

#include <stdio.h> //remove before handing in

void		add_inf_to_m_obj(t_m_object *sprite, char *line, int i, int safe)
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
		sprite->textures = (int*)malloc(sizeof(int) * safe);//need to protect
		sprite->face_ang = (int*)malloc(sizeof(int) * safe);//need to protect
	}
	if (i > 4 && i < sprite->amount + 4)
	{
		if (i % 2 == 1)
			sprite->textures[(i - 5) / 2] = safe;
		else
			sprite->face_ang[(i - 6) / 2] = safe;
	}
}

t_m_object	mov_object_inf(int fd, int sector)
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
		add_inf_to_m_obj(&m_sprite, line, i, safe);
		free(line);
		i++;
	}
	return (m_sprite);
}

void	create_sidedef(t_lib *col_lib, int fd, int len, int i)
{
	static int	k;
	static int	wall_int;
	int			j;

	if (!k)
	{
		k = 0;
		wall_int = 0;
	}
	else
		wall_int = wall_int + col_lib->sector[i].i_sidedefs;
	j = 0;
	col_lib->sector[i] = sector_inf(fd, col_lib->len_tex_lib);
	col_lib->sector[i].i_sidedefs = wall_int;
	while (j < col_lib->sector[i].n_sidedefs)
	{
		col_lib->sidedef[k] = wall_inf(fd, i, col_lib->len_tex_lib, len);
		if (col_lib->sidedef[k].action == 2 && \
		col_lib->sidedef[k].opp_sector != -1)
		{
			create_mv_sidedef(&col_lib->sidedef, k, col_lib->len_sidedef);
			col_lib->len_sidedef++;
			col_lib->sector[i].n_sidedefs++;
			k++;
			j++;
		}
		k++;
		j++;
	}
	wall_int = wall_int + col_lib->sector[i].n_sidedefs;
}

void	create_object(t_lib *col_lib, int fd, int i)
{
	static int	l;
	static int	obj_int;
	int			j;

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
}

void	add_inf_to_lib(t_lib *col_lib, int len, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (i < len)
	{
		create_sidedef(col_lib, fd, len, i);//check this is correct
		create_object(col_lib, fd, i);
		//check this is correct when objs is available
		i++;
	}
	j = 0;
	get_line(&line, fd, "the moving object number can not be read", 1);
	col_lib->n_mov_sprites = ft_atoi(line);
	col_lib->mov_sprites = \
	(t_m_object*)malloc(sizeof(t_m_object) * col_lib->n_mov_sprites);
	while (j < col_lib->n_mov_sprites)
	{
		col_lib->mov_sprites[j] = mov_object_inf(fd, j);
		j++;
	}
}
