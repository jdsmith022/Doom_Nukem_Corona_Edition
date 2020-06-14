/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strstr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 11:52:59 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/02/11 11:46:21 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_resetpointer(const char *haystack, int k)
{
	while (k > 0)
	{
		haystack--;
		k--;
	}
	return (haystack);
}

static int			ft_haystackloop(const char *needle)
{
	int k;

	k = 0;
	while (needle[k] != '\0')
		k++;
	return (k);
}

char				*ft_strstr(const char *haystack, const char *needle)
{
	int	j;
	int k;

	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	k = ft_haystackloop(needle);
	while (*haystack != '\0')
	{
		j = 0;
		while (*haystack == needle[j])
		{
			haystack++;
			j++;
			if (needle[j] == '\0')
			{
				haystack = ft_resetpointer(haystack, k);
				return ((char *)haystack);
			}
		}
		if (haystack == '\0')
			return (0);
		haystack = ft_resetpointer(haystack, j) + 1;
	}
	return (0);
}
