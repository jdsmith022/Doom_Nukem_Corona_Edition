/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:43:57 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/27 18:19:15 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

void	int_check(t_doom *doom, char *line, int line_num)
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
				doom_exit_failure(doom, "error: file reading");
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

static void	get_line_loop(t_doom *doom, char **line, int fd, int ret)
{
	while (*line[0] == '\0' || *line[0] == '#')
	{
		if (ret != 1)
		{
			free(*line);
			doom_exit_failure(doom, "error: get line from file");
		}
		if (*line[0] == '\0' || *line[0] == '#')
		{
			line_num(1);
			free(*line);
			ret = get_next_line2(fd, line);
		}
	}
}

int		get_line(t_doom *doom, char **line, int fd, int is_int)
{
	int ret;

	ret = get_next_line2(fd, line);
	line_num(1);
	if (ret != 1)
	{
		free(*line);
		doom_exit_failure(doom, "error: get line from file");
	}
	get_line_loop(doom, line, fd, ret);
	if (is_int == 1)
	{
		int_check(doom, *line, line_num(0));
		return (ft_atoi(*line));
	}
	return (0);
}
