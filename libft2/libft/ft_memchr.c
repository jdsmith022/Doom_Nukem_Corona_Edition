/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memchr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 15:48:36 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/16 16:04:33 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char*)s;
	while (i < n)
	{
		if (*str == (unsigned char)c)
			return ((void *)&s[i]);
		i++;
		str++;
	}
	return (0);
}
