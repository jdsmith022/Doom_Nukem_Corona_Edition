/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 10:29:57 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/06 20:49:29 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst) != NULL)
	{
		del((*alst), (*alst)->content_size);
		*alst = NULL;
		free(*alst);
	}
}
