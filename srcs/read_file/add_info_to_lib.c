#include "../../includes/doom.h"
#include "../../includes/action.h"

#include <stdio.h> //remove before handing in

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
		// sprite->face_ang = (int*)malloc(sizeof(int) * safe);
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

static void		create_sidedef(t_doom *doom, int fd, int len,
					int i)
{
	t_lib		*col_lib;
	static int	k;
	static int	wall_int;
	static int	total_sd_index = 0;
	int			j;

	col_lib = &doom->lib;
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
		col_lib->sidedef[k].id = total_sd_index;
		if (col_lib->sidedef[k].action == 2 && \
		col_lib->sidedef[k].opp_sector != -1)
		{
			k++;
			create_mv_sidedef(doom, col_lib->sidedef, k);
			col_lib->len_sidedef++;
			col_lib->sector[i].n_sidedefs++;
			j++;
			total_sd_index++;
			printf("move_sidedef action: %d, static action = %d\n", col_lib->sidedef[k].action, col_lib->sidedef[k - 1].action);
		}
		k++;
		j++;
		total_sd_index++;
	}
	wall_int = wall_int + col_lib->sector[i].n_sidedefs;
}

static void		create_object(t_lib *col_lib, int fd, int i,
					int total_sprites)
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

	// printf("n_objects: %d\n", col_lib->sector[i].n_objects);
	while (j < col_lib->sector[i].n_objects)
	{
		col_lib->sprites[l] = object_inf(fd, i, col_lib->len_obj_lib);
		// col_lib->sprites[l] = object_inf(fd, i, col_lib->sector[i].n_objects);
		l++;
		j++;
	}
	obj_int = obj_int + j;
	if (obj_int > total_sprites)
	{
		printf("obj_int: %d, total_sprite: %d\n", obj_int, total_sprites);
		exit_with_error("Error: number of objects in file is incorrect\n");
	}
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
		create_object(&doom->lib, fd, i, doom->total_sprites);
		//check this is correct when objs is available
		i++;
	}
	j = 0;
	get_line(&line, fd, "the moving object number can not be read", 1);
	col_lib->n_mov_sprites = ft_atoi(line);
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
