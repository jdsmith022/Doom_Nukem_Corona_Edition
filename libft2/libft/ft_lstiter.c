/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 14:56:22 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/23 15:02:13 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL || *f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
