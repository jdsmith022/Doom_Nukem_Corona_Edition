#include "../../includes/doom.h"

t_sector			*save_sectors(t_doom *doom, int fd, int *len)
{
	t_sector	*sect;
	char		*line;

	get_line(&line, fd,\
		"the amount of sectors is not specified or can not be read", 1);
	*len = ft_atoi(line);
	// printf("len: %d\n", *len);
	// printf("n_sectors: %d\n", doom->lib.n_sectors);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
	if (sect == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	free(line);
	return (sect);
}

t_sidedef			*save_walls(t_doom *doom, int fd, int *len)
{
	t_sidedef	*walls;
	char		*line;

	get_line(&line, fd,\
		"the amount of walls is not specified or can not be read", 1);
	*len = ft_atoi(line);
	walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * *len);
	if (walls == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	free(line);
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
	// printf("total_sprites: %d\n", *total_sprites);
	sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * *total_sprites);
	if (sprites == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	free(line);
	return (sprites);
}
