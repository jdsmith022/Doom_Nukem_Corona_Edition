 #include "../../includes/doom.h"

 #include <stdio.h>

void        add_inf_to_sect(t_sector *sector, int safe, int i, int tex_len)
{
	if (i == 0)
	{
		if (safe <= 20 && safe >= 0)
		{
			sector->light_level = (double)safe / 10.0;
			sector->light = TRUE;
		}
		else
			error("light level not valid", line_num(0));
	}
	if (i == 1)
		sector->height_floor = safe;
	if (i == 2)
	{
		if (safe >= 0 && safe < tex_len)
			sector->txt_floor = safe;
		else
			error("texture is not available", line_num(0));
	}
	if (i == 3)
		sector->slope_floor = safe;
	if (i == 4)
		sector->height_ceiling = safe;
	if (i == 5)
	{
		if (safe >= 0 && safe < tex_len)
			sector->txt_ceiling = safe;
		else
			error("texture is not available", line_num(0));
	}
	if (i == 6)
		sector->slope_ceiling = safe;
	if (i == 7)
	{
		if (safe >= 3)
			sector->n_sidedefs = safe;
		else
			error("sector needs atleast 3 sidedefs", line_num(0));
	}
	if (i == 8)
		sector->id = safe;
	if (i == 9)
	{
		if (safe != 0 || safe != 1)
			sector->outside = safe;
		else
			error("outside needs to be 1 or 2 (on or off)", line_num(0));
	}
}

t_sector   sector_inf(int fd, int tex_len)
{
	int i;
	char    *line;
	t_sector sector;
	int		safe;

	i = 0;
	while (i < 10)
	{
		safe = get_line(&line, fd, "sector informations does not exist", 1);
		add_inf_to_sect(&sector, safe, i, tex_len);
		free (line);
		i++;
	}
	return (sector);
}

void        add_inf_to_line(t_sidedef *wall, int i, int safe, int tex_len, int sec_len)
{
	if (i == 0)
	{
		if (safe < sec_len && safe >= -1)
			wall->opp_sector = safe;
		else
			error("sector is not available", line_num(0));
	}
	if (i == 1)
	{
		if (safe >= 0)
			wall->line.start.x = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 2)
	{
		if (safe >= 0)
			wall->line.start.y = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 3)
	{
		if (safe >= 0)
			wall->line.end.x = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 4)
	{
		if (safe >= 0)
			wall->line.end.y = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 5)
		wall->action = safe;
	if (i == 6)
	{
		if (safe > -1 && safe < tex_len)
			wall->txt_1 = safe;
		else
			error("Texture is not available", line_num(0));
	}
	if (i == 7)
	{
		if ((safe == -1 && wall->opp_sector != -1) || (safe >= 0 && safe < tex_len))
			wall->txt_2 = safe;
		else
			error("Texture is not available", line_num(0));
	}
	if (i == 8)
	{
		if (safe > -1 && safe < tex_len)
			wall->txt_3 = safe;
		else
			error("Texture is not available", line_num(0));
	}
	if (i == 9)
		wall->id = safe;
}

t_sidedef   wall_inf(int fd, int sector, int tex_len, int sec_len)
{
	int i;
	char    *line;
	t_sidedef wall;
	int     safe;

	i = 0;
	wall.sector = sector;
	while (i < 10)
	{
		safe = get_line(&line, fd, "wall informations does not exist", 1);
		add_inf_to_line(&wall, i, safe, tex_len, sec_len);
		free(line);
		i++;
	}
	return (wall);
}

void        add_inf_to_obj(t_sprite *sprite, char *line, int i, int safe, int obj_len)
{
	if (i == 0)
		sprite->index = safe; //maybe can be done without string copy
	if (i == 1)
	{
		if (safe > 0)
			sprite->pos.x = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 2)
	{
		if (safe > 0)
			sprite->pos.y = safe;
		else
			error("Impossible to have negative coordinates", line_num(0));
	}
	if (i == 3)
		sprite->action = safe;
	if (i == 4)
		sprite->size = safe;
	if (i == 5)
	{
		if (safe > 0)
		{
			sprite->amount = safe;
			sprite->textures = (int*)malloc(sizeof(int) * safe); //need to protect
			sprite->lines = (t_line*)malloc(sizeof(t_line) * safe);//need to protect
		}
		else
			error("Sprite needs a texture", line_num(0));

	}
	if (i > 5 && i < sprite->amount * 5 + 6)
	{
		if (i % 5 == 1)
		{
			// printf("test texture %d\n", safe);
			if (safe >= 0 && safe < obj_len)
				sprite->textures[(i - 6) / 5] = safe;
			else
				error("Sprite texture is not available", line_num(0));
		}
		if (i % 5 == 2)
		{
			// printf("test start x %d\n", safe);
			if (safe > 0)
				sprite->lines[(i - 6) / 5].start.x = safe;
			else
				error("Impossible to have negative coordinates", line_num(0));
		}
		if (i % 5 == 3)
		{
			// printf("test start y %d\n", safe);
			if (safe > 0)
				sprite->lines[(i - 6) / 5].start.y = safe;
			else
				error("Impossible to have negative coordinates", line_num(0));
		}
		if (i % 5 == 4)
		{
			// printf("test end x %d\n", safe);
			if (safe > 0)
				sprite->lines[(i - 6) / 5].end.x = safe;
			else
				error("Impossible to have negative coordinates", line_num(0));
		}
		if (i % 5 == 0)
		{
			// printf("test end y %d\n", safe);
			if (safe > 0)
				sprite->lines[(i - 6) / 5].end.y = safe;
			else
				error("Impossible to have negative coordinates", line_num(0));
		}
	}
}

t_sprite   object_inf(int fd, int sector, int obj_len)
{
	int i;
	char    *line;
	t_sprite sprite;
	int     safe;

	i = 0;
	(void)sector;
	sprite.amount = 0;
	while (i < 6 + sprite.amount * 5)
	{
		// if (i < 5)
		safe = get_line(&line, fd, "object informations does not exist", 1);
		// else
		//     get_line(&line, fd, "object informations does not exist", 0);
		add_inf_to_obj(&sprite, line, i, safe, obj_len);
		sprite.sector = sector; //added to safe sector of sprite
		free(line);
		i++;
	}
	return (sprite);
}

void        add_inf_to_m_obj(t_m_object *sprite, char *line, int i, int safe)
{
	if (i == 0)
		sprite->name = line; //maybe can be done without string copy
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
		// sprite->face_ang = (int*)malloc(sizeof(int) * safe);//need to protect
	}
	if (i > 4 && i < sprite->amount + 4)
	{
		if (i % 2 == 1)
			sprite->textures[(i - 5) / 2] = safe;
		else
			sprite->face_ang[(i - 6) / 2] = safe;
	}
}

t_m_object   mov_object_inf(int fd, int sector)
{
	int i;
	char    *line;
	t_m_object m_sprite;
	int     safe;

	(void)sector;
	i = 0;
	m_sprite.amount = 0;
	while (i < 5 + m_sprite.amount)
	{
		if (i > 0)
		safe = get_line(&line, fd, "moving object informations does not exist", 1);
		else
			get_line(&line, fd, "moving object name does not exist", 0);
		add_inf_to_m_obj(&m_sprite, line, i, safe);
		free(line);
		i++;
	}
	return (m_sprite);
}

void    add_inf_to_lib(t_lib *col_lib, int len, int fd)
{
	int i;
	int j;
	int k;
	int l;
	int wall_int;
	int obj_int;
	char *line;

	i = 0;
	k = 0;
	l = 0;
	wall_int = 0;
	obj_int = 0;
	while (i < len)
	{
		col_lib->sector[i] = sector_inf(fd, col_lib->len_tex_lib);
		j = 0;
		col_lib->sector[i].i_sidedefs = wall_int;
		while (j < col_lib->sector[i].n_sidedefs)
		{
			col_lib->sidedef[k] = wall_inf(fd, i, col_lib->len_tex_lib, len);
			if (col_lib->sidedef[k].action == 2 && col_lib->sidedef[k].opp_sector != -1)
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
		wall_int =  wall_int + col_lib->sector[i].n_sidedefs; //check this is correct
		get_line(&line, fd, "the object number can not be read", 1);
		col_lib->sector[i].n_objects = ft_atoi(line);
		free(line);
		col_lib->sector[i].i_objects = obj_int;
		j = 0;
		while (j < col_lib->sector[i].n_objects)
		{
			col_lib->sprites[l] = object_inf(fd, i, col_lib->len_obj_lib);
			l++;
			j++;
		}
		obj_int =  obj_int + j; //check this is correct when objs is available
		i++;
	}
	j = 0;
	get_line(&line, fd, "the moving object number can not be read", 1);
	col_lib->n_mov_sprites = ft_atoi(line);
	col_lib->mov_sprites = (t_m_object*)malloc(sizeof(t_m_object) * col_lib->n_mov_sprites);
	while (j < col_lib->n_mov_sprites)
	{
		col_lib->mov_sprites[j] = mov_object_inf(fd, j);
		j++;
	}
	wall_int =  wall_int + col_lib->sector[i].i_sidedefs;
}
