/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 15:48:00 by efrank         #+#    #+#                */
/*   Updated: 2019/03/14 13:19:24 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_buff(const int fd, t_list **head)
{
	t_list	*temp;

	if (!(*head))
	{
		*head = ft_lstnew("", 1);
		(*head)->content_size = fd;
		return (*head);
	}
	temp = *head;
	if (fd == (int)(*head)->content_size)
		return (*head);
	while (temp->next)
	{
		if (fd == (int)temp->content_size)
			break ;
		temp = temp->next;
	}
	if (fd == (int)temp->content_size)
		return (temp);
	temp->next = ft_lstnew("", 1);
	temp = temp->next;
	temp->content_size = fd;
	return (temp);
}

static int		get_new_string(t_list **buff2, char **line, char *temp)
{
	char *temp2;

	if (ft_strcmp((*buff2)->content, "\0") == 0)
	{
		*line = NULL;
		return (0);
	}
	if (!temp && !ft_strlen((*buff2)->content))
	{
		(*buff2)->content = NULL;
		return (0);
	}
	if (!temp)
	{
		*line = ft_strdup((*buff2)->content);
		free((*buff2)->content);
		(*buff2)->content = ft_strnew(0);
		return (1);
	}
	*temp = '\0';
	*line = ft_strdup((*buff2)->content);
	temp2 = ft_strdup(temp + 1);
	free((*buff2)->content);
	(*buff2)->content = temp2;
	return (1);
}

static int		read_once(t_list *buff2, char **temp, int fd)
{
	ssize_t size;
	char	buff[BUFF_SIZE + 1];

	size = read(fd, buff, BUFF_SIZE);
	if (size == -1)
		return (-1);
	buff[size] = '\0';
	*temp = buff2->content;
	buff2->content = ft_strjoin(buff2->content, buff);
	if (*temp)
		free(*temp);
	*temp = ft_strchr(buff2->content, '\n');
	return (size);
}

static int		read_loop(t_list *buff2, char **temp, int fd, ssize_t size)
{
	char	buff[BUFF_SIZE + 1];

	size = read(fd, buff, BUFF_SIZE);
	if (size == -1)
		return (-1);
	if (!size)
		return (0);
	buff[size] = '\0';
	*temp = buff2->content;
	buff2->content = ft_strjoin(buff2->content, buff);
	if (*temp)
		free(*temp);
	return (size);
}

int				get_next_line(const int fd, char **line)
{
	static t_list		*head;
	t_list				*buff2;
	ssize_t				size;
	char				*temp;

	if (fd < 0)
		return (-1);
	buff2 = get_buff(fd, &head);
	if (buff2->content == NULL)
	{
		*line = NULL;
		return (0);
	}
	size = read_once(buff2, &temp, fd);
	if (size == -1)
		return (-1);
	while (size && !temp)
	{
		size = read_loop(buff2, &temp, fd, size);
		if (size == -1)
			return (-1);
		temp = ft_strchr(buff2->content, '\n');
	}
	return (get_new_string(&buff2, line, temp));
}
