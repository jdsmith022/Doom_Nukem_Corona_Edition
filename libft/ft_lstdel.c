/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 10:52:30 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:27:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*temp;

	node = *alst;
	while (node != NULL)
	{
		del(node->content, node->content_size);
		temp = node->next;
		free(node);
		node = temp;
	}
	*alst = NULL;
}
