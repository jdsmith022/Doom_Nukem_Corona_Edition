/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank        #+#    #+#                 */
/*   Updated: 2019/01/07 18:09:40 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dstlen;
	size_t srclen;
	size_t i;
	size_t j;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	j = dstlen;
	if (dstlen >= size)
		return (size + srclen);
	while ((size - dstlen) > 1 && src[i])
	{
		dst[j++] = src[i++];
		size--;
	}
	dst[j] = '\0';
	return (srclen + dstlen);
}
