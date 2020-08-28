/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sky.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:30 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 09:45:51 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static void		free_bmp_pixels(t_bmp *images)
{
	size_t i;

	i = 0;
	while (i < 5)
	{
		free(images[i].pixels);
		i++;
	}
}

static t_line	*init_sky_sd(t_doom *doom)
{
	t_line *sky_sd;

	sky_sd = (t_line*)malloc(sizeof(t_line) * 4);
	if (sky_sd == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
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

static void		save_sky_2(t_doom *doom, t_bmp *images,\
						SDL_Surface **lib, int sky_fd)
{
	sky_fd = open("assets/textures/sky_box/meadow_up.bmp", O_RDONLY);
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[0] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 0);
	sky_fd = open("assets/textures/sky_box/meadow_rt.bmp", O_RDONLY);
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[1] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 1);
	sky_fd = open("assets/textures/sky_box/meadow_ft.bmp", O_RDONLY);
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[2] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 2);
	sky_fd = open("assets/textures/sky_box/meadow_lf.bmp", O_RDONLY);
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[3] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 3);
	sky_fd = open("assets/textures/sky_box/meadow_bk.bmp", O_RDONLY);
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[4] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 4);
}

SDL_Surface		**save_sky(t_doom *doom, t_line **sky_sd)
{
	SDL_Surface	**lib;
	t_bmp		*images;
	int			sky_fd;

	images = malloc_images_lib(doom, 5);
	lib = malloc_sdl_lib(doom, images, 5);
	doom->lib.len_sky_lib = 5;
	save_sky_2(doom, images, lib, sky_fd);
	free_bmp_pixels(images);
	free(images);
	close(sky_fd);
	*sky_sd = init_sky_sd(doom);
	return (lib);
}
