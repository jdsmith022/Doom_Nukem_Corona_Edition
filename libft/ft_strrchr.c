/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:22:42 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:22:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = ft_strlen(s);
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	while (i > 0)
	{
		i--;
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
	}
	return (NULL);
}
