#include "../../includes/doom.h"
#include "../../includes/read.h"

static t_line		*init_sky_sd(t_doom *doom)
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
	sky_fd = open_file("assets/textures/sky_box/meadow_dn.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);		
	images[1] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 1);
	sky_fd = open_file("assets/textures/sky_box/meadow_rt.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);		
	images[2] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 2);
	sky_fd = open_file("assets/textures/sky_box/meadow_ft.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[3] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 3);
	sky_fd = open_file("assets/textures/sky_box/meadow_lf.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[4] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 4);
	sky_fd = open_file("assets/textures/sky_box/meadow_bk.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[5] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 5);
}

SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd)
{
	SDL_Surface	**lib;
	t_bmp		*images;
	int			sky_fd;

	images = malloc_images_lib(doom, 6);
	lib = malloc_sdl_lib(doom, images, 6);
	doom->lib.len_sky_lib = 6;
	save_bpm_to_sdl(doom, images, lib, 1);
	sky_fd = open_file("assets/textures/sky_box/meadow_up.bmp");
	if (sky_fd < 0)
		bmp_safe_exit(doom, images);
	images[0] = read_bmp(sky_fd);
	save_bpm_to_sdl(doom, images, lib, 0);
	save_sky_2(doom, images, lib, sky_fd);
	free(images);
	close(sky_fd);
	*sky_sd = init_sky_sd(doom);
	return (lib);
}
