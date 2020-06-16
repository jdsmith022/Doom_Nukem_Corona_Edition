/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank         #+#    #+#                */
/*   Updated: 2019/11/14 12:31:08 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*byte1;
	unsigned char	*byte2;
	size_t			i;

	i = 0;
	byte1 = (unsigned char *)s1;
	byte2 = (unsigned char *)s2;
	while (i < n)
	{
		if (byte1[i] != byte2[i])
			return (byte1[i] - byte2[i]);
		i++;
	}
	return (0);
}
