/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:12 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 16:58:35 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

t_sector			*save_sectors(t_doom *doom, int fd, int *len)
{
	t_sector	*sect;
	char		*line;

	get_line(doom, &line, fd, 1);
	*len = ft_atoi(line);
	free(line);
	printf("len: %d\n", *len);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * (*len));
	if (sect == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (sect);
}

t_sidedef			*save_walls(t_doom *doom, int fd, int *len)
{
	t_sidedef	*walls;
	char		*line;

	get_line(doom, &line, fd, 1);
	*len = ft_atoi(line);
	free(line);
	get_line(doom, &line, fd, 1);
	*len += ft_atoi(line);
	free(line);
	walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * *len);
	if (walls == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (walls);
}

t_sprite			*save_sprites(t_doom *doom, int fd, int *total_sprites)
{
	t_sprite	*sprites;
	char		*line;

	get_line(doom, &line, fd, 1);
	*total_sprites = ft_atoi(line);
	free(line);
	sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * *total_sprites);
	if (sprites == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (sprites);
}
