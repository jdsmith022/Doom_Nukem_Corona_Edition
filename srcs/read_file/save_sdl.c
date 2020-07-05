/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sdl.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 15:35:53 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/05 16:03:56 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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

static void			malloc_images_lib(t_bmp *images,
						SDL_Surface **lib, int len)
{
	t_bmp *temp_images;
	SDL_Surface **temp_lib;

	temp_images = images;
	temp_images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (temp_images == NULL)
		doom_exit_failure(NULL, MALLOC_ERR);
	images = &temp_images;
	temp_lib = lib;
	temp_lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (temp_lib == NULL)
		doom_exit_lib_failure(images, MALLOC_ERR);
	lib = &temp_lib;
}

SDL_Surface			**save_sky(void)
{
	SDL_Surface	**lib;
	t_bmp		*images;
	int			sky_fd;

	images = malloc_images_lib(images, 6);
	lib = malloc_sdl_lib(lib, 6);
	sky_fd = open_file("textures/sky_box/meadow_bk.bmp");
	images[0] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 0);
	sky_fd = open_file("textures/sky_box/meadow_dn.bmp");
	images[1] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 1);
	sky_fd = open_file("textures/sky_box/meadow_ft.bmp");
	images[2] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 2);
	sky_fd = open_file("textures/sky_box/meadow_lf.bmp");
	images[3] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 3);
	sky_fd = open_file("textures/sky_box/meadow_rt.bmp");
	images[4] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 4);
	sky_fd = open_file("textures/sky_box/meadow_up.bmp");
	images[5] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 5);
	return (lib);
}

static SDL_Surface	**read_from_line(char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	t_bmp		*images;
	int			fd;
	int			index;

	images = malloc_images_lib(images, 6);
	lib = malloc_sdl_lib(lib, 6);
	index = 0;
	while (index < len)
	{
		get_line(&line, map_fd, "not enough texture names", 0);
		fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			index++;
			continue ;
		}
		printf("here\n");
		images[index] = read_bmp(fd);
		save_bpm_to_sdl(images, lib, index);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface			**save_img(int map_fd)
{
	char		*line;
	int			len;

	get_line(&line, map_fd,\
		"the amount of textures is not specified or can not be read", 1);
	len = ft_atoi(line);
	return (read_from_line(line, map_fd, len));
}
