/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memccpy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 15:26:43 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/16 11:38:13 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned int	i;

	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		*dest = *source;
		if (*source == (unsigned char)c)
			return (&dst[i + 1]);
		i++;
		dest++;
		source++;
	}
	return (0);
}
