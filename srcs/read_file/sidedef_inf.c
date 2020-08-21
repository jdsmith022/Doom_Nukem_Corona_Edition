#include "../../includes/doom.h"

static void	add_coordinates(t_sidedef *wall, int i, int safe)
{
	if (safe < 0 && i > 0 && i < 5)
		error("Impossible to have negative coordinates", line_num(0));
	if (i == 1)
		wall->line.start.x = safe;
	if (i == 2)
		wall->line.start.y = safe;
	if (i == 3)
		wall->line.end.x = safe;
	if (i == 4)
		wall->line.end.y = safe;
}

static void	add_texture_sd(t_sidedef *wall, int i, int safe, int tex_len)
{
	if (safe <= -1 && safe >= tex_len && i > 5 && i < 9)
		error("Texture is not available", line_num(0));
	if (i == 6)
		wall->txt_1 = safe;
	if (i == 7)
		wall->txt_2 = safe;
	if (i == 8)
		wall->txt_3 = safe;
}

static void	add_inf_to_line(t_sidedef *wall, int i, int safe, int tex_len, int sec_len)
{
	if (i == 0)
	{
		if (safe < sec_len && safe >= -1)
			wall->opp_sector = safe;
		else
			error("sector is not available", line_num(0));
	}
	add_coordinates(wall, i, safe);
	if (i == 5)
		wall->action = safe;
	add_texture_sd(wall, i, safe, tex_len);
	if (i == 9)
		wall->id = safe;
}

t_sidedef	wall_inf(int fd, int sector, int tex_len, int sec_len)
{
	int			i;
	char		*line;
	t_sidedef	wall;
	int			safe;

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
