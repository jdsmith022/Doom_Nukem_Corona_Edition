#include "doom_nukem.h"
#include <stdio.h>

t_sector  *save_sectors(int fd, int *len)
{
    t_sector    *sect;
    char        *line;
    int         ret;

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
    int         ret;

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
    int         ret;

    get_line(&line, fd, "the amount of stationary sprites is not specified or can not be read", 1);
    len = ft_atoi(line);
    sprites = (t_object*)ft_memalloc(sizeof(t_object) * len);
    free(line);
    return (sprites);
}

t_exture   *save_img(int fd)
{
    int ret;
    int i;
    char *line;
    int len;
    t_exture *lib;
 
    get_line(&line, fd, "the amount of textures is not specified or can not be read", 1);
    len = ft_atoi(line);
    lib = (t_exture*)ft_memalloc(sizeof(t_exture) * len);
    i = 0;
    while (i < len)
    {
        get_line(&line, fd, "not enough texture names", 0);
		// data->textures[i].img = mlx_xpm_file_to_image(&data->textures[i].xvar,\
		// line, &data->textures[i].width, &data->textures[i].height);
		// if (data->textures[i].img == NULL)
		// 	error("texture does not exist", fd);
		// data->textures[i].address = mlx_get_data_addr(data->textures[i].img, &data->textures[i].b_p_p, &data->textures[i].size_line, &data->textures[i].endian);
		free(line);
		i++;
    }
    return (lib);
}
