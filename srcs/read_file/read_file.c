#include "../../includes/doom.h"
#include "../../includes/read.h"

t_sector			*save_sectors(t_doom *doom, int fd, int *len)
{
	t_sector	*sect;
	char		*line;

	get_line(&line, fd,\
		"the amount of sectors is not specified or can not be read", 1);
	*len = ft_atoi(line);
	free(line);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
	if (sect == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (sect);
}

t_sidedef			*save_walls(t_doom *doom, int fd, int *len)
{
	t_sidedef	*walls;
	char		*line;

	get_line(&line, fd,\
		"the amount of walls is not specified or can not be read", 1);
	*len = ft_atoi(line);
	free(line);
	get_line(&line, fd,\
		"the amount of moving walls is not specified", 1);
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

	get_line(&line, fd,\
		"the amount of stationary sprites is not specified or can not be read",\
		1);
	*total_sprites = ft_atoi(line);
	free(line);
	sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * *total_sprites);
	if (sprites == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (sprites);
}
