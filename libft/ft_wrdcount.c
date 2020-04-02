/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wrdcount.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 18:45:24 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/11 18:25:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wrdcount(char const *s, char c)
{
	size_t j;

	j = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			return (j);
		if (((*s != c) && (*(s + 1) == c)) || (*(s + 1) == 0))
			j++;
		s++;
	}
	return (j);
}
