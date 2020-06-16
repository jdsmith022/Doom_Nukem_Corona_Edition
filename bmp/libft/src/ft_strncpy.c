/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank         #+#    #+#                */
/*   Updated: 2019/11/12 16:58:23 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!len)
		return (dst);
	while (src[i] && len > 0)
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	while (len > 0)
	{
		dst[i] = '\0';
		i++;
		len--;
	}
	return (dst);
}
