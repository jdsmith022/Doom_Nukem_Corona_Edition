#include "../../includes/doom.h"
#include "game_editor.h"

void    add_to_fd(int num, int fd)
{
    ft_putnbr_fd(num, fd);
    ft_putchar_fd('\n', fd);
}

void    printing_sidedef(t_gamedesign *design, int i, int fd)
{
    add_to_fd(design->sidedef[i].opp_sector, fd);
    add_to_fd(design->sidedef[i].line.start.x, fd);
    add_to_fd(design->sidedef[i].line.start.y, fd);
    add_to_fd(design->sidedef[i].line.end.x, fd);
    add_to_fd(design->sidedef[i].line.end.y, fd);
    add_to_fd(design->sidedef[i].action, fd);
    add_to_fd(design->sidedef[i].txt_1, fd);
    add_to_fd(design->sidedef[i].txt_2, fd);
    add_to_fd(design->sidedef[i].txt_3, fd);
    add_to_fd(design->sidedef[i].id, fd);
}

void    printing_sector(t_gamedesign *design, int i, int fd)
{
    int j;

    add_to_fd(design->sector[i].light, fd);
    add_to_fd(design->sector[i].height_floor, fd);
    add_to_fd(design->sector[i].txt_floor, fd);
    add_to_fd(design->sector[i].slope_floor, fd);
    add_to_fd(design->sector[i].height_ceiling, fd);
    add_to_fd(design->sector[i].txt_ceiling, fd);
    add_to_fd(design->sector[i].slope_ceiling, fd);
    add_to_fd(design->sector[i].n_sidedefs, fd);
    add_to_fd(0, fd);
    add_to_fd(design->sector[i].id, fd);
    add_to_fd(1, fd);
    ft_putchar_fd('\n', fd);
    j = design->sector[i].i_sidedefs;
    while (j < design->sector[i].n_sidedefs + design->sector[i].i_sidedefs)
    {
        printing_sidedef(design, j, fd);
        j++;
        ft_putchar_fd('\n', fd);
    }
}

void    printing_map(t_gamedesign *design)
{
    int fd;
    int i;

    fd = open("game_editor_level", O_WRONLY);
    add_to_fd(design->s_len, fd);
    add_to_fd(design->w_len, fd);
    add_to_fd(0, fd);
    ft_putchar_fd('\n', fd);
    i = 0;
    while (i <= design->s_len)
    {
        printing_sector(design, i, fd);
        i++;
    }
}