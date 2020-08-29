/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:27:30 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:27:30 by jesmith       ########   odam.nl         */
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
