/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memcmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 16:20:14 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/16 18:31:30 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char		*str1;
	const char		*str2;
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	str1 = s1;
	str2 = s2;
	i = 0;
	while (i < n)
	{
		if (*str1 != *str2)
		{
			a = *str1;
			b = *str2;
			return (a - b);
		}
		i++;
		str1++;
		str2++;
	}
	return (0);
}
