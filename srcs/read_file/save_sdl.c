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
		get_line(&line, map_fd, "not enough texture names", 0);
		fd = open(line, O_RDONLY);
		if (fd < 0)
			bmp_safe_exit(doom, images);
		images[index] = read_bmp(fd);
		if (images == NULL)
			bmp_safe_exit(doom, images);
		save_bpm_to_sdl(doom, images, lib, index);
		set_texture_type(doom, line, lib[index]);
		free(line);
		index++;
	}
	free(images);
	return (lib);
}

SDL_Surface			**save_objects(t_doom *doom, int map_fd, int *len)
{
	char		*line;

	get_line(&line, map_fd,\
		"the amount of objects is not specified or can not be read", 1);
	*len = ft_atoi(line);
	return (read_from_line(doom, line, map_fd, *len));
}

SDL_Surface			**save_textures(t_doom *doom, int map_fd, int *len)
{
	char		*line;

	get_line(&line, map_fd,\
		"the amount of textures is not specified or can not be read", 1);
	*len = ft_atoi(line);
	return (read_from_line(doom, line, map_fd, *len));
}
