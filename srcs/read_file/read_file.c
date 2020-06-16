#include "../../includes/doom.h"
#include <stdio.h>

t_sector  *save_sectors(int fd, int *len)
{
    t_sector    *sect;
    char        *line;

    get_line(&line, fd, "the amount of sectors is not specified or can not be read", 1);
    *len = ft_atoi(line);
    sect = (t_sector*)ft_memalloc(sizeof(t_sector) * *len);
    free(line);
    return (sect);
}

t_sidedef  *save_walls(int fd)
{
    t_sidedef   *walls;
    char        *line;
    int         len;

    get_line(&line, fd, "the amount of walls is not specified or can not be read", 1);
    len = ft_atoi(line);
    walls = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * len);
    free(line);
    return (walls);
}

t_object  *save_sprites(int fd)
{
    t_object   *sprites;
    char        *line;
    int         len;

    get_line(&line, fd, "the amount of stationary sprites is not specified or can not be read", 1);
    len = ft_atoi(line);
    sprites = (t_object*)ft_memalloc(sizeof(t_object) * len);
    free(line);
    return (sprites);
}

t_bmp   *save_img(int map_fd)
{
    int     i;
    char    *line;
    int     len;
    t_bmp   *images;
    int     fd;

    get_line(&line, map_fd, "the amount of textures is not specified or can not be read", 1);
    len = ft_atoi(line);
    images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
    i = 0;w
    printf("LENGTH : %d\n", len);
    while (i < len)
    {
        get_line(&line, map_fd, "not enough texture names", 0);
        fd = open(line, O_RDONLY);
        printf("FD : %d\n", fd);
        if (fd < 0){
            i++;
            continue ;
        }
        images[i] = read_bmp(fd);
        print_meta_data(images[i].info);
		free(line);
		i++;
    }
    return (images);
}
