/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 13:56:07 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/08 15:02:17 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	new = ft_stralloc(s);
	if (!new)
		return (NULL);
	while (s[i] != '\0')
	{
		new[j] = f(i, s[i]);
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
