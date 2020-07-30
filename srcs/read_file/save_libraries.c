#include "../../includes/doom.h"

int		open_file(char *filename)
{
	int		fd;
    char *message;

    message = ft_strjoin(filename, "can't open");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(message, 0);
	return (fd);
}

void	save_libraries(t_doom *doom)
{
	int fd;

    // if (argc != 1)
    //     error("Please compile program in this fashion: ./duke_nukem", 0);
    // fd = open_file("srcs/read_file/new_level");
    fd = open_file("srcs/read_file/new_level2");
    doom->lib.tex_lib = save_textures(doom, fd, &doom->lib.len_tex_lib);
    doom->lib.obj_lib = save_objects(doom, fd, &doom->lib.len_obj_lib);
    doom->lib.sky_lib = save_sky(doom, &doom->lib.sky_sd);
    doom->lib.sector = save_sectors(doom, fd, &doom->lib.n_sectors);
    doom->lib.sidedef = save_walls(doom, fd,  &doom->lib.len_sidedef);
    doom->lib.sprites = save_sprites(doom, fd, &doom->total_sprites);
    add_inf_to_lib(&doom->lib, doom->lib.n_sectors, fd);
    close(fd);
    // create_header(&list, &len);
    // parsed_list = parse(list, len); //this is called cursing or something
    // bytecode = create_bytecode(parsed_list);
    // printf("%s\n", parsed_list);
}
