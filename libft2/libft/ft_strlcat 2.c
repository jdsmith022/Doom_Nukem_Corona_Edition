/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlcat.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 20:00:54 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/24 11:40:11 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t length;
	size_t i;

	length = ft_strlen(dst);
	i = 0;
	if (length >= size)
		return (ft_strlen(src) + size);
	while (src[i] && ((length + i) < (size - 1)))
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (length + ft_strlen(src));
}
