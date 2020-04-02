/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddback.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 21:19:20 by jesmith        #+#    #+#                */
/*   Updated: 2020/01/08 10:19:39 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **alst, t_list *blst)
{
	t_list	*temp;

	temp = *alst;
	if (temp == NULL)
	{
		*alst = blst;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = blst;
}
