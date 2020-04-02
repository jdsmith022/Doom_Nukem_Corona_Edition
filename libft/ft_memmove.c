/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 16:33:59 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:40:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dest;
	const char	*source;

	dest = dst;
	source = src;
	i = 0;
	if (source < dest)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dest[i] = source[i];
		}
	}
	else
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return ((void *)(dst));
}
