/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 13:32:08 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/23 15:18:17 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list *current;

	current = *alst;
	if (current != NULL)
	{
		del(current->content, current->content_size);
		free(current);
		*alst = NULL;
	}
}
