/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sdl.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:24 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 00:46:28 by JessicaSmit   ########   odam.nl         */
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

static void			safe_read_line_exit(t_doom *doom, t_bmp *images,
						char *line)
{
	free(line);
	bmp_safe_exit(doom, images);
}

static SDL_Surface	**read_from_line(t_doom *doom, char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	t_bmp		*images;
	int			fd;
	int			index;

	lib = malloc_sdl_lib(doom, images, len);
	index = 0;
	while (index < len)
	{
		get_line(doom, &line, map_fd, 0);
		fd = open(line, O_RDONLY);
		if (fd < 0)
			safe_read_line_exit(doom, images, line);
		images = (t_bmp*)ft_memalloc(sizeof(t_bmp));
		*images = read_bmp(fd);
		if (images == NULL)
			safe_read_line_exit(doom, images, line);
		save_bpm_to_sdl(doom, images, lib, index);
		free(images->pixels);
		free(images);
		set_texture_type(doom, line, lib[index]);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface			**save_objects(t_doom *doom, int map_fd, int *len)
{
	char		*line;
	SDL_Surface **lib;
	int			ret;

	ret = get_line(doom, &line, map_fd, 1);
	*len = ft_atoi(line);
	lib = read_from_line(doom, line, map_fd, *len);
	free(line);
	return (lib);
}

SDL_Surface			**save_textures(t_doom *doom, int map_fd, int *len)
{
	char		*line;
	SDL_Surface **lib;
	int			ret;

	ret = get_line(doom, &line, map_fd, 1);
	*len = ft_atoi(line);
	lib = read_from_line(doom, line, map_fd, *len);
	free(line);
	return (lib);
}
