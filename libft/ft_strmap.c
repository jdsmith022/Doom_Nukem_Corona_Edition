/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/28 14:06:18 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/08 15:02:06 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i] != '\0')
	{
		new[j] = f(s[i]);
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
