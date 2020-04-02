/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 11:31:48 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/07 17:59:53 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t c;
	size_t i;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (i < len && haystack[i] != '\0')
	{
		c = 0;
		while (haystack[i + c] == needle[c] && i + c < len)
		{
			if (needle[c + 1] == '\0')
				return ((char *)&haystack[i]);
			c++;
		}
		i++;
	}
	return (NULL);
}
