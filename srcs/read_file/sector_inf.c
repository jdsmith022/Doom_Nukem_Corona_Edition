/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sector_inf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:34 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/04 12:47:27 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static void	add_texture_sect(t_sector *sector, int safe, int i)
{
	if (i == 2)
		sector->txt_floor = safe;
	if (i == 6)
		sector->txt_ceiling = safe;
}

static void	add_amounts(t_doom *doom, t_sector *sector, int safe, int i)
{
	if (i == 9)
	{
		if (safe >= 3)
			sector->n_sidedefs = safe;
		else
			doom_exit_read_failure(doom, \
				"error: sector needs atleast 3 sidedefs", line_num(0));
	}
	if (i == 10)
	{
		if (safe >= 0)
			sector->n_objects = safe;
		else
			doom_exit_read_failure(doom, \
				"error: object numbers can not be negative", line_num(0));
	}
	if (i == 12)
	{
		if (safe != 0 || safe != 1)
			sector->action = safe;
		else
			doom_exit_read_failure(doom, \
				"error: action needs to be 1 or 2 (on or off)", line_num(0));
	}
}

static void	add_light(t_doom *doom, t_sector *sector, int safe, int i)
{
	if (i == 0)
	{
		if (safe <= 20 && safe >= 0)
		{
			sector->light_level = (double)safe / 10.0;
			sector->light = TRUE;
		}
		else
			doom_exit_read_failure(doom, \
				"error: light level not valid", line_num(0));
	}
}

static void	add_inf_to_sect(t_sector *sector, int safe, int i)
{
	if (i == 1)
		sector->height_floor = safe;
	add_texture_sect(sector, safe, i);
	if (i == 3)
		sector->slope_floor = safe * (PI / 180);
	if (i == 4)
		sector->slope_floor_id = safe;
	if (i == 5)
		sector->height_ceiling = safe;
	if (i == 7)
		sector->slope_ceiling = safe * (PI / 180);
	if (i == 8)
		sector->slope_ceiling_id = safe;
	if (i == 11)
		sector->id = safe;
}

t_sector	sector_inf(t_doom *doom, int fd, int tex_len)
{
	int			i;
	char		*line;
	t_sector	sector;
	int			safe;

	i = 0;
	while (i < 13)
	{
		safe = get_line(doom, &line, fd, 1);
		free(line);
		if ((i == 2 || i == 6) && safe < 0 && safe >= tex_len)
			doom_exit_read_failure(doom, \
				"error: texture is not available", line_num(0));
		add_light(doom, &sector, safe, i);
		add_inf_to_sect(&sector, safe, i);
		add_amounts(doom, &sector, safe, i);
		i++;
	}
	return (sector);
}
