 #include "doom_nukem.h"

 #include <stdio.h>

void        add_inf_to_sect(t_sector *sector, char *line, int i)
{
    int safe;

    //ft_is_line_int(line);
    safe = ft_atoi(line);
    if (i == 0)
        sector->light_level = safe;
    if (i == 1)
        sector->height_floor = safe;
    if (i == 2)
        sector->texture_floor = safe;
    if (i == 3)
        sector->slope_floor = safe;
    if (i == 4)
        sector->height_ceiling = safe;
    if (i == 5)
        sector->texture_ceiling = safe;
    if (i == 6)
        sector->slope_ceiling = safe;
    if (i == 7)
        sector->n_sidedefs = safe;
}

t_sector   sector_inf(int fd)
{
    int i;
    char    *line;
    t_sector sector;

    i = 0;
    while (i < 8)
    {
        get_line(&line, fd, "sector informations does not exist", 1);
        add_inf_to_sect(&sector, line, i);
        free (line);
        i++;
    }
    return (sector);
}

void        add_inf_to_line(t_sidedef *wall, int i, int safe)
{
    if (i == 0)
        wall->portal = safe; //can only be one or two
    if (i == 1)
        wall->start.x = safe;
    if (i == 2)
        wall->start.y = safe;
    if (i == 3)
        wall->end.x = safe;
    if (i == 4)
        wall->end.y = safe;
    if (i == 5)
        wall->action = safe;
    if (i == 6)
        wall->texture_1 = safe;
    if (i == 7)
        wall->texture_2 = safe;
    if (i == 8)
        wall->texture_3 = safe;
    if (i == 9)
        wall->opp = safe;
}

t_sidedef   wall_inf(int fd, int sector)
{
    int i;
    char    *line;
    int     ret;
    t_sidedef wall;
    int     safe;

    i = 0;
    wall.sector = sector;
    while (i < 10)
    {
        safe = get_line(&line, fd, "wall informations does not exist", 1);
        add_inf_to_line(&wall, i, safe);
        free(line);
        i++;
    }
    return (wall);
}

void        add_inf_to_obj(t_object *sprite, char *line, int i, int safe)
{
    if (i == 0)
        sprite->name = line; //maybe can be done without string copy
    if (i == 1)
        sprite->location.start.x = safe;
    if (i == 2)
        sprite->location.start.y = safe;
    if (i == 3)
        sprite->location.end.x = safe;
    if (i == 4)
        sprite->location.end.y = safe;
    if (i == 5)
        sprite->action = safe;
    if (i == 6)
    {
        sprite->n_textures = safe;
        sprite->textures = (int*)malloc(sizeof(int) * safe);
        sprite->face_ang = (int*)malloc(sizeof(int) * safe);

    }
    if (i > 6 && i < sprite->n_textures + 6)
    {
        if (i % 2 == 1)
            sprite->textures[(i - 7) / 2] = safe;
        else
            sprite->face_ang[(i - 8) / 2] = safe;
    }
}

t_object   object_inf(int fd, int sector)
{
    int i;
    char    *line;
    int     ret;
    t_object sprite;
    int     safe;

    i = 0;
    sprite.n_textures = 0;
    while (i < 6 + sprite.n_textures)
    {
        // if (i < 5)
        safe = get_line(&line, fd, "object informations does not exist", 1);
        // else
        //     get_line(&line, fd, "object informations does not exist", 0);
        add_inf_to_obj(&sprite, line, i, safe);
        free(line);
        i++;
    }
    return (sprite);
}

void        add_inf_to_m_obj(t_m_object *sprite, char *line, int i, int safe)
{
    if (i == 0)
        sprite->name = line; //maybe can be done without string copy
    if (i == 1)
        sprite->action = safe;
    if (i == 2)
        sprite->speed = safe;
    if (i == 3)
        sprite->spawn_time = safe;
    if (i == 4)
    {
        sprite->n_textures = safe;
        sprite->textures = (int*)malloc(sizeof(int) * safe);
        sprite->face_ang = (int*)malloc(sizeof(int) * safe);

    }
    if (i > 4 && i < sprite->n_textures + 4)
    {
        if (i % 2 == 1)
            sprite->textures[(i - 5) / 2] = safe;
        else
            sprite->face_ang[(i - 6) / 2] = safe;
    }
}
t_m_object   mov_object_inf(int fd, int sector)
{
    int i;
    char    *line;
    int     ret;
    t_m_object m_sprite;
    int     safe;

    i = 0;
    m_sprite.n_textures = 0;
    while (i < 5 + m_sprite.n_textures)
    {
        if (i > 0)
        safe = get_line(&line, fd, "moving object informations does not exist", 1);
        else
            get_line(&line, fd, "moving object name does not exist", 0);
        add_inf_to_m_obj(&m_sprite, line, i, safe);
        free(line);
        i++;
    }
    return (m_sprite);
}

void    add_inf_to_lib(t_lib *col_lib, int len, int fd)
{
    int i;
    int j;
    int k;
    int l;
    int wall_int;
    int obj_int;
    int ret;
    char *line;

    i = 0;
    k = 0;
    l = 0;
    wall_int = 0;
    obj_int = 0;
    while (i < len)
    {
        col_lib->sector[i] = sector_inf(fd);
        j = 0;
        col_lib->sector[i].start_walls = wall_int;
        col_lib->sector[i].end_walls = wall_int + col_lib->sector[i].start_walls; 
        while (j < col_lib->sector[i].n_sidedefs)
        {
            col_lib->walls[k] = wall_inf(fd, i);
            k++;
            j++;
        }
        wall_int =  wall_int + col_lib->sector[i].start_walls;
        get_line(&line, fd, "the object number can not be read", 1);
        col_lib->sector[i].n_objects = ft_atoi(line);
        free(line);
        col_lib->sector[i].start_obj = obj_int;
        col_lib->sector[i].end_obj = obj_int + col_lib->sector[i].start_obj; 
        j = 0;
        while (j < col_lib->sector[i].n_sidedefs)
        {
            col_lib->sprites[k] = object_inf(fd, i);
            l++;
            j++;
        }
        obj_int =  obj_int + col_lib->sector[i].start_obj;
        i++;
    }
    j = 0;
    get_line(&line, fd, "the moving object number can not be read", 1);
    col_lib->n_mov_sprites = ft_atoi(line);
    col_lib->mov_sprites = (t_m_object*)malloc(sizeof(t_m_object) * col_lib->n_mov_sprites);
    while (j < col_lib->n_mov_sprites)
    {
        col_lib->mov_sprites[j] = mov_object_inf(fd, j);
        j++;
    }
    wall_int =  wall_int + col_lib->sector[i].start_walls;
}