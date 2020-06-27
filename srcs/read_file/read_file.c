#include "../../includes/doom.h"
#include <stdio.h>

t_sector  *save_sectors(int fd, int *len)
{
	t_sector    *sect;
	char        *line;

	get_line(&line, fd, "the amount of sectors is not specified or can not be read", 1);
	*len = ft_atoi(line);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
	free(line);
	return (sect);
}

t_sidedef  *save_walls(int fd)
{
	t_sidedef   *walls;
	char        *line;
	int         len;

	get_line(&line, fd, "the amount of walls is not specified or can not be read", 1);
	len = ft_atoi(line);
	walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * len);
	free(line);
	return (walls);
}

t_object  *save_sprites(int fd)
{
	t_object   *sprites;
	char        *line;
	int         len;

	get_line(&line, fd, "the amount of stationary sprites is not specified or can not be read", 1);
	len = ft_atoi(line);
	sprites = (t_object*)ft_memalloc(sizeof(t_object) * len);
	free(line);
	return (sprites);
}

static SDL_Surface    **save_img_array(t_bmp *images, char *line, int map_fd, int len)
{
	SDL_Surface **lib;
	int         fd;
	int         index;

	index = 0;
	lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (lib == NULL)
		doom_exit_lib_failure(images, MALLOC_ERR);
	while (index < len)
	{
		get_line(&line, map_fd, "not enough texture names", 0);
		fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			index++;
			continue ;
		}
		images[index] = read_bmp(fd);
		// printf("images: %s", images[index].array);
		lib[index] = SDL_CreateRGBSurface(0, images[index].info.width, images[index].info.height,\
			32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		if (lib[index] == NULL)
			doom_exit_lib_failure(images, MALLOC_ERR);
		ft_memcpy(lib[index]->pixels, images[index].pixels,\
			(images[index].info.width * images[index].info.height));
		printf("lib: %s", lib[index]->pixels);
		print_meta_data(images[index].info);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface         **save_img(int map_fd)
{
	t_bmp       *images;
	char        *line;
	int         len;

	get_line(&line, map_fd, "the amount of textures is not specified or can not be read", 1);
	len = ft_atoi(line);
	images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (images == NULL)
		doom_exit_failure(NULL, MALLOC_ERR);
	return (save_img_array(images, line, map_fd, len));
}
