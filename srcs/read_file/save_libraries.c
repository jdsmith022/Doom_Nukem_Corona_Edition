#include "../../includes/doom.h"
#include "../../includes/read.h"

int				open_file(t_doom *doom, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		doom_exit_failure(doom, "error: can't open level file");
	return (fd);
}

static void		modified(void)
{
	struct stat filestat;

	stat("srcs/read_file/start_skybox_full", &filestat);
	/* turn on and add the last modified date before handing in*/
	// if (ft_strcmp(ctime(&filestat.st_mtime), "Tue Jul 21 11:47:15 2020\n") != 0)
	//     error("file has been modified", 0);
}

void			save_libraries(t_doom *doom)
{
	int fd;

	// if (argc != 1)
	//     error("Please run program in this fashion: ./duke_nukem", 0);
	modified();
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
