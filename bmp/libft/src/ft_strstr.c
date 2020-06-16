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

#include <stdlib.h>
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i])
	{
		while (haystack[i] && haystack[i++] == needle[j++])
		{
			if (!needle[j])
				return ((char *)&haystack[i - j]);
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}
