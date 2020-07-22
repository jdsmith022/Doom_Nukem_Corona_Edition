/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 15:35:53 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/22 12:06:51 by jesmith       ########   odam.nl         */
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

t_line		*init_sky_sd()
{
	t_line *sky_sd;

	sky_sd = (t_line*)malloc(sizeof(t_line) * 4);
	sky_sd[0].start.x = 0;
	sky_sd[0].start.y = 0;
	sky_sd[0].end.x = 125;
	sky_sd[0].end.y = 0;
	sky_sd[1].start.x = 125;
	sky_sd[1].start.y = 125;
	sky_sd[1].end.x = 125;
	sky_sd[1].end.y = 0;
	sky_sd[2].start.x = 125;
	sky_sd[2].start.y = 125;
	sky_sd[2].end.x = 0;
	sky_sd[2].end.y = 125;
	sky_sd[3].start.x = 0;
	sky_sd[3].start.y = 125;
	sky_sd[3].end.x = 0;
	sky_sd[3].end.y = 0;
	return (sky_sd);
}

SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd)
{
	SDL_Surface	**lib;
	t_bmp		*images;
	int			sky_fd;

	images = malloc_bmp(doom, 6);
	lib = malloc_sdl(doom, images, 6);
	doom->lib.len_sky_lib = 6;
	sky_fd = open_file("textures/sky_box/meadow_up.bmp");
	images[0] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 0);
	sky_fd = open_file("textures/sky_box/meadow_dn.bmp");
	images[1] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 1);
	sky_fd = open_file("textures/sky_box/meadow_rt.bmp");
	images[2] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 2);
	sky_fd = open_file("textures/sky_box/meadow_ft.bmp");
	images[3] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 3);
	sky_fd = open_file("textures/sky_box/meadow_lf.bmp");
	images[4] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 4);
	sky_fd = open_file("textures/sky_box/meadow_bk.bmp");
	images[5] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 5);
	*sky_sd = init_sky_sd();
	return (lib);
}

static SDL_Surface	**read_from_line(t_doom *doom, char *line,
						int map_fd, int len)
{
	SDL_Surface **lib;
	t_bmp		*images;
	int			fd;
	int			index;

	images = malloc_bmp(doom, len);
	lib = malloc_sdl(doom, images, len);
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
		images[index] = read_bmp(fd);
		save_bpm_to_sdl(images, lib, index);
		free(line);
		index++;
	}
	return (lib);
}

SDL_Surface			**save_img(t_doom *doom, int map_fd, int *len)
{
	char		*line;

	get_line(&line, map_fd,\
		"the amount of textures is not specified or can not be read", 1);
	*len = ft_atoi(line);
	return (read_from_line(doom, line, map_fd, *len));
}
