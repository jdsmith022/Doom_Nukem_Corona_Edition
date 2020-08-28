/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 21:49:55 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:27:05 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char *c;
	unsigned const char *d;

	i = 0;
	c = s1;
	d = s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (c[i] != d[i])
			break ;
		i++;
	}
	return ((int)c[i] - d[i]);
}
