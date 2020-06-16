/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 12:29:24 by fhignett      #+#    #+#                 */
/*   Updated: 2019/01/16 12:29:24 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *new;

	if (!lst || !f)
		return (NULL);
	new = f(lst);
	if (!new)
		return (NULL);
	head = new;
	lst = lst->next;
	while (lst)
	{
		new->next = f(lst);
		if (!new->next)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
