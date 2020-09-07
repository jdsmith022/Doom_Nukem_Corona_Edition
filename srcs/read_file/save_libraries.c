/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_libraries.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 10:01:08 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

int			open_file(t_doom *doom, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		doom_exit_failure(doom, "error: can't open level file");
	return (fd);
}

void		modified(t_doom *doom, char *file_name)
{
	struct stat filestat;

	stat(file_name, &filestat);
	if ((long long)filestat.st_mtime != (long long)filestat.st_birthtime)
		doom_exit_failure(doom, "error: file has been modified");
}

void		save_libraries(t_doom *doom)
{
	int fd;

	modified(doom, "srcs/read_file/start_skybox_full");
	fd = open_file(doom, "srcs/read_file/start_skybox_full");
	doom->game_design.sym_lib = save_textures(doom, fd, &doom->lib.len_tex_lib);
	doom->lib.tex_lib = save_textures(doom, fd, &doom->lib.len_tex_lib);
	doom->lib.obj_lib = save_objects(doom, fd, &doom->lib.len_obj_lib);
	if (doom->game.editor == FALSE)
	{
		doom->lib.sky_lib = save_sky(doom, &doom->lib.sky_sd);
		doom->lib.sector = save_sectors(doom, fd, &doom->lib.n_sectors);
		doom->lib.sidedef = save_walls(doom, fd, &doom->lib.len_sidedef);
		doom->lib.sprites = save_sprites(doom, fd, &doom->total_sprites);
		add_inf_to_lib(doom, doom->lib.n_sectors, fd);
	}
	close(fd);
}
