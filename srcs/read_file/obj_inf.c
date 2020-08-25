/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_inf.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:46:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/25 11:06:01 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

void		add_coordinates_obj(t_doom *doom, t_sprite *sprite, int i, int safe)
{
	int	mod;

	mod = i % 5;
	if (((((mod > 1 && mod < 5) || mod == 0) && i > 6 && \
	i < sprite->amount * 5 + 7) || i == 1 || i == 2) && safe < 0)
		doom_exit_read_failure(doom, \
			"error: impossible to have negative coordinates", line_num(0));
	if (i == 1)
		sprite->pos.x = safe;
	else if (i == 2)
		sprite->pos.y = safe;
	else if (mod == 3)
		sprite->lines[(i - 7) / 5].start.x = safe;
	else if (mod == 4)
		sprite->lines[(i - 7) / 5].start.y = safe;
	else if (mod == 0)
		sprite->lines[(i - 7) / 5].end.x = safe;
	else if (mod == 1)
		sprite->lines[(i - 7) / 5].end.y = safe;
}

static void	malloc_lines(t_doom *doom, t_sprite *sprite, int safe)
{
	if (safe > 0)
	{
		sprite->amount = safe;
		sprite->textures = (int*)malloc(sizeof(int) * safe);
		sprite->lines = (t_line*)malloc(sizeof(t_line) * 4);
		if (sprite->textures == NULL || sprite->lines == NULL)
			doom_exit_failure(doom, "error: malloc for objects");
	}
	else
		doom_exit_read_failure(doom, \
			"error: Sprite needs a texture", line_num(0));
}

static int	add_lines(t_sprite *sprite, int i, int safe, int obj_len)
{
	if (i > 6 && i < sprite->amount * 5 + 7)
	{
		if (i % 5 == 2)
		{
			if (safe >= 0 && safe < obj_len)
				sprite->textures[(i - 7) / 5] = safe;
			else
				return (-1);
		}
		return (1);
	}
	return (0);
}

static void	add_inf_to_obj(t_doom *doom, t_sprite *sprite, int i, int safe)
{
	if (i == 0)
	{
		sprite->index = safe;
	}
	else if (i == 1 || i == 2)
		add_coordinates_obj(doom, sprite, i, safe);
	else if (i == 3)
	{
		sprite->action = safe;
	}
	else if (i == 4)
	{
		sprite->size = safe;
	}
	else if (i == 5)
		sprite->block = safe;
}

t_sprite	object_inf(t_doom *doom, int fd, int sector, int obj_len)
{
	int			i;
	char		*line;
	t_sprite	sprite;
	int			safe;
	int			ret;

	i = 0;
	sprite.amount = 0;
	while (i < 7 + 4 * 5)
	{
		safe = get_line(doom, &line, fd, 1);
		add_inf_to_obj(doom, &sprite, i, safe);
		if (i == 6)
			malloc_lines(doom, &sprite, safe);
		ret = add_lines(&sprite, i, safe, obj_len);
		if (ret == -1)
			doom_exit_read_failure(doom, \
					"error: Sprite texture is not available", line_num(0));
		if (ret == 1)
			add_coordinates_obj(doom, &sprite, i, safe);
		sprite.sector = sector;
		free(line);
		i++;
	}
	return (sprite);
}
