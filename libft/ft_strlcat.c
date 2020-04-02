/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 18:54:04 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/04 09:33:34 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	j = 0;
	while (size < dlen + 1)
		return (slen + size);
	if (size > dlen + 1)
	{
		while (i < size - 1 && src[j] != '\0')
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		*(dst + i) = '\0';
	}
	return (dlen + slen);
}
