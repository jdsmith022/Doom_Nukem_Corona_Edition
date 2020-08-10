#include "../../includes/doom.h"

static void	add_texture_sect(t_sector *sector, int safe, int i, int tex_len)
{
	if ((i == 2 || i == 6) && safe < 0 && safe >= tex_len)
		error("texture is not available", line_num(0));
	if (i == 2)
		sector->txt_floor = safe;
	if (i == 6)
		sector->txt_ceiling = safe;
}

static void	add_amounts(t_sector *sector, int safe, int i)
{
	if (i == 9)
	{
		if (safe >= 3)
			sector->n_sidedefs = safe;
		else
			error("sector needs atleast 3 sidedefs", line_num(0));
	}
	if (i == 10)
	{
		if (safe >= 0)
		{
			sector->n_objects = safe;
		}
		else
			error("object numbers can not be negative", line_num(0));
	}
	if (i == 12)
	{
		if (safe != 0 || safe != 1)
			sector->action = safe;
		else
			error("action needs to be 1 or 2 (on or off)", line_num(0));
	}
}

static void	add_light(t_sector *sector, int safe, int i)
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
}

static void	add_inf_to_sect(t_sector *sector, int safe, int i, int tex_len)
{
	add_light(sector, safe, i);
	if (i == 1)
		sector->height_floor = safe;
	add_texture_sect(sector, safe, i, tex_len);
	if (i == 3)
		sector->slope_floor = safe;
	if (i == 4)
		sector->slope_floor_id = safe;
	if (i == 5)
		sector->height_ceiling = safe;
	if (i == 7)
		sector->slope_ceiling = safe;
	if (i == 8)
		sector->slope_ceiling_id = safe;
	if (i == 11)
		sector->id = safe;
	add_amounts(sector, safe, i);
}

t_sector	sector_inf(int fd, int tex_len)
{
	int			i;
	char		*line;
	t_sector	sector;
	int			safe;

	i = 0;
	while (i < 13)
	{
		safe = get_line(&line, fd, "sector informations does not exist", 1);
		add_inf_to_sect(&sector, safe, i, tex_len);
		free(line);
		i++;
	}
	return (sector);
}
