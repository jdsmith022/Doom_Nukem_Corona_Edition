#include "../../includes/doom.h"

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