#include "doom_nukem.h"
#include <stdio.h> //replace for ft_printf before handing in

void    int_check(char *line, char *er, int line_num)
{
    int i;
    int check;

    i = 0;
    while(i < ft_strlen(line))
    {
        check = ft_isdigit(line[i]);
        if (check == 0)
        {
            if (line[i] != '-')
                error(er, line_num);
        }
        i++;
    }
}

int     get_line(char **line, int fd, char *er, int is_int)
{
    int ret;
    static int line_num;

    if (!line_num)
        line_num = 0;
    line_num++;
    ret = get_next_line(fd, line);
    if (ret != 1)
            error(er, line_num);
    while(*line[0] == '\0' || *line[0] == '#')
    {
        if (ret != 1)
            error(er, line_num);
        if (*line[0] == '\0' || *line[0] == '#')
        {
            free(*line);
            line_num++;
            ret = get_next_line(fd, line);
        }
    }
    if (is_int == 1)
    {
        int_check(*line, er, line_num);
        return (ft_atoi(*line));
    }
    return(0);
}


void    error(char *error, int line_num)
{
    printf("line %i: %s\n", line_num, error);
    exit(0);
}