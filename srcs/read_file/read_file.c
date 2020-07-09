/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 15:35:26 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/09 15:05:33 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_sector			*save_sectors(int fd, int *len)
{
	t_sector	*sect;
	char		*line;

	get_line(&line, fd,\
		"the amount of sectors is not specified or can not be read", 1);
	*len = ft_atoi(line);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
	free(line);
	return (sect);
}

t_sidedef			*save_walls(int fd)
{
	t_sidedef	*walls;
	char		*line;
	int			len;

	get_line(&line, fd,\
		"the amount of walls is not specified or can not be read", 1);
	len = ft_atoi(line);
	walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * len);
	free(line);
	return (walls);
}

t_sprite			*save_sprites(int fd, int *total_sprites)
{
	t_sprite	*sprites;
	char		*line;
	int			len;

	get_line(&line, fd,\
		"the amount of stationary sprites is not specified or can not be read",\
		1);
	len = ft_atoi(line);
	*total_sprites = len;
	sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * len);
	free(line);
	return (sprites);
}
