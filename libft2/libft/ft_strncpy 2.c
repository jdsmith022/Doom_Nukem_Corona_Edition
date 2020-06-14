/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strncpy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 18:14:44 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/24 09:11:14 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int		i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
