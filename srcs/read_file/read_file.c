/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 15:43:35 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/05 13:29:52 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_sector  		*save_sectors(int fd, int *len)
{
	t_sector    *sect;
	char        *line;

	get_line(&line, fd,\
		"the amount of sectors is not specified or can not be read", 1);
	*len = ft_atoi(line);
	sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
	free(line);
	return (sect);
}

t_sidedef  			*save_walls(int fd)
{
	t_sidedef   *walls;
	char        *line;
	int         len;

	get_line(&line, fd,\
		"the amount of walls is not specified or can not be read", 1);
	len = ft_atoi(line);
	walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * len);
	free(line);
	return (walls);
}

t_object  			*save_sprites(int fd)
{
	t_object   *sprites;
	char        *line;
	int         len;

	get_line(&line, fd,\
		"the amount of stationary sprites is not specified or can not be read",\
		1);
	len = ft_atoi(line);
	sprites = (t_object*)ft_memalloc(sizeof(t_object) * len);
	free(line);
	return (sprites);
}

static void			save_bpm_to_sdl(t_bmp *images,
						SDL_Surface **lib, int index)
{
	lib[index] = SDL_CreateRGBSurface(0, \
		images[index].info.width, images[index].info.height,\
		24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (lib[index] == NULL)
		doom_exit_lib_failure(images, MALLOC_ERR);
	ft_memcpy(lib[index]->pixels, images[index].pixels,\
		(images[index].info.img_size));
	// print_meta_data(images[index].info);
}

static SDL_Surface	**read_from_line(t_bmp *images, char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	int			fd;
	int			index;

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
		save_bpm_to_sdl(images, lib, index);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface			**save_sky(void)
{
	char	*line;
	int		sky_fd;

	sky_fd
	get_line()
}

SDL_Surface			**save_img(int map_fd)
{
	t_bmp		*images;
	char		*line;
	int			len;

	get_line(&line, map_fd,\
		"the amount of textures is not specified or can not be read", 1);
	len = ft_atoi(line);
	images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (images == NULL)
		doom_exit_failure(NULL, MALLOC_ERR);
	return (read_from_line(images, line, map_fd, len));
}
