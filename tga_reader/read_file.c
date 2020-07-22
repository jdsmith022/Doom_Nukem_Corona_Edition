#include "../includes/doom.h"

static int	free_list(t_list *list, char **file)
{
	*file = NULL;
	ft_lstdel(&list, &ft_del);
	return (-1);
}

static char	*list_to_string(t_list *list, size_t len)
{
	size_t	index;
	t_list	*next;
	char	*str;

	index = 0;
	if (list == NULL)
		return (ft_strnew(0));
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (list != NULL)
	{
		if (list->content != NULL)
			ft_memcpy(&str[index], list->content, list->content_size);
		index += list->content_size;
		next = list->next;
		ft_lstdelone(&list, &ft_del);
		list = next;
	}
	return (str);
}

static int	add_to_list(t_list **list, t_list **prev, char *buff, ssize_t len)
{
	t_list *temp;

	temp = ft_lstnew((void *)buff, len);
	if (temp == NULL)
		return (-1);
	if (*list == NULL)
		*list = temp;
	else
		(*prev)->next = temp;
	*prev = temp;
	return (0);
}

int		read_file_for_tga(char **file, int fd)
{
	t_list	*list;
	t_list	*prev;
	char	buff[BUFF_SIZE + 1];
	ssize_t	ret;
	ssize_t	len;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	len = 0;
	list = NULL;
	ret = read(fd, buff, BUFF_SIZE);
	while (ret > 0)
	{
		len += ret;
		if (add_to_list(&list, &prev, buff, ret) == -1)
			return (free_list(list, file));
		ret = read(fd, buff, BUFF_SIZE);
	}
	if (ret < 0)
		return (free_list(list, file));
	*file = list_to_string(list, len);
	if (file == NULL)
		return (free_list(list, file));
	return (0);
}
