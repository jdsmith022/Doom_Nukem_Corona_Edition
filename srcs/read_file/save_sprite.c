#include "../../includes/doom.h"

// static void			save_tga_to_sdl(t_tga *images,
// 						SDL_Surface **lib, int index)
// {
// 	lib[index] = SDL_CreateRGBSurface(0, \
// 		images[index].header.width, images[index].header.height,\
// 		24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
// 	if (lib[index] == NULL)
// 		doom_exit_lib_failure(images, MALLOC_ERR);
// 	ft_memcpy(lib[index]->pixels, images[index].pixels,\
// 		(images[index].header.pitch));
// }

static SDL_Surface	**read_from_line(t_doom *doom, char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	t_tga		*images;
	int			fd;
	int			index;

	images = malloc_tga(doom, len);
	lib = malloc_sdl(doom, images, len);
	index = 0;
	while (index < len)
	{
		get_line(&line, map_fd, "not enough texture names", 0);
		printf("%s\n", line);
		fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			index++;
			continue ;
		}
		images[index] = tga_reader(doom, fd);
		// save_tga_to_sdl(images, lib, index);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface			**save_sprite(t_doom *doom, int map_fd, int *len)
{
	char		*line;

	get_line(&line, map_fd,\
		"the amount of textures is not specified or can not be read", 1);
	*len = ft_atoi(line);
	return (read_from_line(doom, line, map_fd, *len));
}
