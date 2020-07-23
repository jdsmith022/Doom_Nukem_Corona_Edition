/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sky.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 11:49:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/23 11:49:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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

static void		save_sky_2(t_bmp *images,\
						SDL_Surface **lib, int sky_fd)
{
	images[4] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 4);
	sky_fd = open_file("textures/sky_box/meadow_bk.bmp");
	images[5] = read_bmp(sky_fd);
	save_bpm_to_sdl(images, lib, 5);
}

SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd)
{
	SDL_Surface	**lib;
	t_bmp		*images;
	int			sky_fd;

	images = malloc_images_lib(doom, 6);
	lib = malloc_sdl_lib(doom, images, 6);
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
	save_sky_2(images, lib, sky_fd);
	free(images);
	*sky_sd = init_sky_sd();
	return (lib);
}
