/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 11:32:18 by jesmith        #+#    #+#                */
/*   Updated: 2020/01/04 13:35:14 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *head;
	t_list *last;

	if (lst == NULL || f == NULL)
		return (NULL);
	head = f(lst);
	if (!head)
		return (NULL);
	last = head;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new = f(lst);
		if (new == NULL)
		{
			ft_lstdel(&new, &ft_del);
			return (NULL);
		}
		ft_lstaddback(&last, new);
	}
	return (head);
}
