/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank        #+#    #+#                 */
/*   Updated: 2020/07/08 13:33:48 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		tmp[len];
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	i = 0;
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		d[i] = tmp[i];
		i++;
	}
	return (dst);
}
