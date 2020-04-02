/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 11:19:36 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/05 15:52:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *temp;

	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}
