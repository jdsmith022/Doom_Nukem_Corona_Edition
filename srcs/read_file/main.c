#include "doom_nukem.h"
#include <stdio.h>

int     open_file(char *filename)
{
	int		fd;

    // printf("hello");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("file can't open", 0);
    return (fd);
}
int     main(int argc, char **argv)
{
    t_lib col_lib;
    int      fd;
    int     len;

    if (argc != 1)
        error("Please compile program in this fashion: ./duke_nukem", 0);
    fd = open_file("level_1");
    col_lib.tex_lib = save_img(fd);
    col_lib.obj_lib = save_img(fd);
    col_lib.sector = save_sectors(fd, &len);
    col_lib.walls = save_walls(fd);
    col_lib.sprites = save_sprites(fd);
    add_inf_to_lib(&col_lib, len, fd);
    // create_header(&list, &len);
    // parsed_list = parse(list, len); //this is called cursing or something
    // bytecode = create_bytecode(parsed_list);
    // printf("%s\n", parsed_list);
    return (0);
}