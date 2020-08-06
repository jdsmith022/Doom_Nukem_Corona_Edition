#include "../../includes/doom.h"

int			open_file(char *filename)
{
	int		fd;
	char 	*message;

	message = ft_strjoin(filename, "can't open");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(message, 0);
	return (fd);
}

static void		modified(void)
{
	struct stat filestat;

	stat("srcs/read_file/the_cross-2", &filestat);
	printf("%s", ctime(&filestat.st_mtime));
	/* turn on and add the last modified date before handing in*/
	// if (ft_strcmp(ctime(&filestat.st_mtime), "Tue Jul 21 11:47:15 2020\n") != 0)
	//     error("file has been modified", 0);
}

void		save_libraries(t_doom *doom)
{
	int fd;

	// if (argc != 1)
	//     error("Please compile program in this fashion: ./duke_nukem", 0);
	modified();
	fd = open_file("srcs/read_file/the_cross-2");
	doom->lib.tex_lib = save_textures(doom, fd, &doom->lib.len_tex_lib);
	printf("1save libraries len_tex_lib: %d\n", doom->lib.len_obj_lib);
	doom->lib.obj_lib = save_objects(doom, fd, &doom->lib.len_obj_lib);
	printf("2save libraries len_tex_lib: %d\n", doom->lib.len_obj_lib);
	doom->lib.sky_lib = save_sky(doom, &doom->lib.sky_sd);
	doom->lib.sector = save_sectors(doom, fd, &doom->lib.n_sectors);
	doom->lib.sidedef = save_walls(doom, fd, &doom->lib.len_sidedef);
	doom->lib.sprites = save_sprites(doom, fd, &doom->total_sprites);
	add_inf_to_lib(doom, &doom->lib, doom->lib.n_sectors, fd);
	close(fd);
}
