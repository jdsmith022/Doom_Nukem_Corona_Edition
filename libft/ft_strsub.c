/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 12:09:03 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 13:43:04 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new = (char *)ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	while (i < len && s[i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
