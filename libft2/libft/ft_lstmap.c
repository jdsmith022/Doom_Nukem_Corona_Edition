/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 15:05:50 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/23 15:13:53 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *ret;

	if (lst == NULL || *f == NULL)
		return (NULL);
	ret = f(lst);
	new = ret;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(lst);
		new = new->next;
	}
	return (ret);
}
