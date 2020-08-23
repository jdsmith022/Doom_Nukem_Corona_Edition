/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:56:39 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/23 10:14:21 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "../includes/doom.h"

int		ft_strsubsize(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\n' && str[i] != '\0' && str[i] != ',' && str[i] != '\r')
		i++;
	if (str[i] == ',' || str[i] == '\r')
		line_num(-1);
	return (i);
}

int		ft_readloop(int fd, char *buf, t_list *item, char **line)
{
	int		ret;
	char	*temp;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		temp = ft_strjoin(item->content, buf);
		free(item->content);
		item->content = ft_strdup(temp);
		free(temp);
		if (ft_strchr(buf, '\n') || ft_strchr(buf, ',') || ft_strchr(buf, '\r'))
			break ;
	}
	if (ret < BUFF_SIZE && ft_strlen(item->content) == 0)
		return (0);
	*line = ft_strsub(item->content, 0, ft_strsubsize(item->content));
	temp = ft_strsub(item->content, ft_strlen(*line) + 1, \
	ft_strlen(item->content) - ft_strlen(*line));
	free(item->content);
	item->content = ft_strdup(temp);
	free(temp);
	return (1);
}

t_list	*ft_content_sizecheck(int fd, t_list *start)
{
	t_list	*temp;
	t_list	*new;

	while (start != NULL)
	{
		if (start->content_size == (size_t)fd)
			return (start);
		temp = start;
		start = start->next;
	}
	new = ft_lstnew("\0", 1);
	if (new == NULL)
		return (NULL);
	new->content_size = (size_t)fd;
	temp->next = new;
	return (new);
}

int		get_next_line2(const int fd, char **line)
{
	char			*buf;
	static t_list	*start;
	t_list			*item;
	int				more;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (buf == NULL)
		return (-1);
	if (read(fd, buf, 0) == -1)
		return (-1);
	if (!start)
	{
		item = ft_lstnew("\0", 1);
		item->content_size = (size_t)fd;
		start = item;
	}
	else
		item = ft_content_sizecheck(fd, start);
	more = ft_readloop(fd, buf, item, line);
	free(buf);
	if (more == -1 || more == 1)
		return (more);
	return (0);
}
