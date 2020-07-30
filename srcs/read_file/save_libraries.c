#include "../../includes/doom.h"

int		open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("file can't open", 0);
	return (fd);
}

static void	modified()
{
	struct stat filestat;

	stat("srcs/read_file/new_level", &filestat);
	printf("%s", ctime(&filestat.st_mtime));
	/* turn on and add the last modified date before handing in*/
	// if (ft_strcmp(ctime(&filestat.st_mtime), "Tue Jul 21 11:47:15 2020\n") != 0)
	//     error("file has been modified", 0);
}

void	save_libraries(t_doom *doom)
{
	int fd;
	int len;

	modified();
	fd = open_file("srcs/read_file/new_level");
	doom->lib.tex_lib = save_img(fd, &doom->lib.len_tex_lib);
	doom->lib.obj_lib = save_img(fd, &doom->lib.len_obj_lib);
	save_font(doom);
	doom->lib.sky_lib = save_sky(&doom->lib.sky_sd);
	doom->lib.sector = save_sectors(fd, &len);
	doom->lib.sidedef = save_walls(fd, &doom->lib.len_sidedef);
	doom->lib.sprites = save_sprites(fd, &doom->total_sprites);
	add_inf_to_lib(&doom->lib, len, fd);
}
