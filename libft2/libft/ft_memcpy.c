/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memcpy.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 12:13:13 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/11 14:52:38 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*dest;
	const unsigned char		*source;
	unsigned int			i;

	dest = dst;
	source = src;
	i = 0;
	while (i < n)
	{
		*dest = *source;
		i++;
		dest++;
		source++;
	}
	return (dst);
}
