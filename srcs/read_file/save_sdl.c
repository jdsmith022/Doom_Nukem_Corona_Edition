/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sdl.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:24 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/27 17:14:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/textures.h"
#include "../../includes/read.h"

void				bmp_safe_exit(t_doom *doom, t_bmp *images)
{
	doom_exit_lib_failure(images, MALLOC_ERR);
	doom_exit_failure(doom, "error: bmp reader");
}

static SDL_Surface	**read_from_line(t_doom *doom, char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	t_bmp		*images;
	int			fd;
	int			index;

	images = malloc_images_lib(doom, len);
	lib = malloc_sdl_lib(doom, images, len);
	index = 0;
	while (index < len)
	{
		get_line(doom, &line, map_fd, 0);
		fd = open(line, O_RDONLY);
		free(line);
		if (fd < 0)
			bmp_safe_exit(doom, images);
		images[index] = read_bmp(fd);
		if (images == NULL)
			bmp_safe_exit(doom, images);
		save_bpm_to_sdl(doom, images, lib, index);
		set_texture_type(doom, line, lib[index]);
		index++;
	}
	free(images);
	return (lib);
}

SDL_Surface			**save_objects(t_doom *doom, int map_fd, int *len)
{
	char		*line;
	SDL_Surface **lib;

	get_line(doom, &line, map_fd, 1);
	*len = ft_atoi(line);
	lib = read_from_line(doom, line, map_fd, *len);
	free(line);
	return (lib);
}

SDL_Surface			**save_textures(t_doom *doom, int map_fd, int *len)
{
	char		*line;
	SDL_Surface **lib;

	get_line(doom, &line, map_fd, 1);
	*len = ft_atoi(line);
	lib = read_from_line(doom, line, map_fd, *len);
	free(line);
	return (lib);
}
