/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 12:42:13 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 13:41:35 by jesmith       ########   odam.nl         */
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
