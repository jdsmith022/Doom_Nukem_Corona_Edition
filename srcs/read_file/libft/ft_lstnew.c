/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 20:06:26 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/21 20:46:51 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (head == NULL)
		return (head);
	if (content == NULL)
	{
		head->content = NULL;
		head->content_size = 0;
		head->next = NULL;
		return (head);
	}
	head->content = malloc(sizeof(void *) * content_size);
	head->content = ft_memcpy(head->content, content, content_size);
	head->content_size = content_size;
	head->next = NULL;
	return (head);
}
