#include "../../includes/doom.h"

int		open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("file can't open", 0);
	return (fd);
}

void	save_libraries(t_doom *doom)
{
	int fd;
	int len;

    // if (argc != 1)
    //     error("Please compile program in this fashion: ./duke_nukem", 0);
    fd = open_file("srcs/read_file/new_level");
    doom->lib.tex_lib = save_img(fd, &doom->lib.len_tex_lib);
    doom->lib.obj_lib = save_img(fd, &doom->lib.len_obj_lib);
    save_font(doom);
    doom->lib.sky_lib = save_sky(&doom->lib.sky_sd);
    doom->lib.sector = save_sectors(fd, &len);
    doom->lib.sidedef = save_walls(fd,  &doom->lib.len_sidedef);
    doom->lib.sprites = save_sprites(fd, &doom->total_sprites);
    add_inf_to_lib(&doom->lib, len, fd);
    // create_header(&list, &len);
    // parsed_list = parse(list, len); //this is called cursing or something
    // bytecode = create_bytecode(parsed_list);
    // printf("%s\n", parsed_list);
}