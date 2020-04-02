/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 10:55:47 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/08 14:10:53 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *str, int c, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*s;

	i = 0;
	dest = dst;
	s = str;
	while (i < n)
	{
		dest[i] = s[i];
		if (s[i] == (unsigned char)c)
		{
			dest[i] = s[i];
			i++;
			return (dst + i);
		}
		i++;
	}
	return (NULL);
}
