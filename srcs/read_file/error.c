#include "../../includes/doom.h"
#include "../../includes/read.h"

void	int_check(char *line, char *er, int line_num)
{
	int i;
	int check;

	i = 0;
	while (i < (int)ft_strlen(line))
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

int		line_num(int i)
{
	static int line_num;

	if (!line_num)
	{
		line_num = 0;
		if (i == -1)
			line_num++;
	}
	if (i == 1)
	{
		line_num++;
		return (0);
	}
	if (i == -1)
	{
		line_num--;
		return (0);
	}
	return (line_num);
}

int		get_line(char **line, int fd, char *er, int is_int)//remove *er add doom and make message error reading map
{
	int ret;

	ret = get_next_line2(fd, line);
	line_num(1);
	if (ret != 1)
		error(er, line_num(0));//doom error exit
	while (*line[0] == '\0' || *line[0] == '#')
	{
		if (ret != 1)
			error(er, line_num(0));
		if (*line[0] == '\0' || *line[0] == '#')
		{
			// free(*line);
			line_num(1);
			ret = get_next_line2(fd, line);
		}
	}
	if (is_int == 1)
	{
		int_check(*line, er, line_num(0));
		return (ft_atoi(*line));
	}
	return (0);
}

void	error(char *error, int line_num)
{
	printf("line %i: %s\n", line_num, error); //remove
	exit(0);
}
