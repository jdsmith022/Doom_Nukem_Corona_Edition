/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_inf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:48 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/25 10:44:48 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static void	add_coordinates(t_doom *doom, t_sidedef *wall, int i, int safe)
{
	if (safe < 0 && i > 0 && i < 5)
		doom_exit_read_failure(doom, \
			"error: impossible to have negative coordinates", line_num(0));
	if (i == 1)
		wall->line.start.x = safe;
	if (i == 2)
		wall->line.start.y = safe;
	if (i == 3)
		wall->line.end.x = safe;
	if (i == 4)
		wall->line.end.y = safe;
}

static void	add_texture_sd(t_sidedef *wall, int i, int safe)
{
	if (i == 6)
		wall->txt_1 = safe;
	if (i == 7)
		wall->txt_2 = safe;
	if (i == 8)
		wall->txt_3 = safe;
}

static void	add_inf_to_line(t_doom *doom, t_sidedef *wall, int i, int safe)
{
	if (i == 5)
		wall->action = safe;
	if (i == 9)
		wall->id = safe;
}

static void	add_opp_sector_info(t_doom *doom, t_sidedef *wall,
				int safe, int sec_len)
{
	if (safe < sec_len && safe >= -1)
		wall->opp_sector = safe;
	else
		doom_exit_read_failure(doom, \
			"error: sector is not available", line_num(0));
}

t_sidedef	wall_inf(t_doom *doom, int fd, int sector, int sec_len)
{
	int			i;
	char		*line;
	t_sidedef	wall;
	int			safe;
	int			tex_len;

	i = 0;
	tex_len = doom->lib.len_tex_lib;
	wall.sector = sector;
	while (i < 10)
	{
		safe = get_line(doom, &line, fd, 1);
		if (safe <= -1 && safe >= tex_len && i > 5 && i < 9)
			doom_exit_read_failure(doom, \
				"error: texture is not available", line_num(0));
		if (i == 0)
			add_opp_sector_info(doom, &wall, safe, sec_len);
		add_inf_to_line(doom, &wall, i, safe);
		add_coordinates(doom, &wall, i, safe);
		add_texture_sd(&wall, i, safe);
		free(line);
		i++;
	}
	return (wall);
}
