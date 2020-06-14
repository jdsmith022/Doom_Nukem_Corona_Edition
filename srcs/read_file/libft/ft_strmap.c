/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 14:55:42 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/17 16:24:20 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	int		i;

	i = 0;
	if (s == NULL || !f)
		return (NULL);
	while (s[i] != '\0')
		i++;
	fresh = (char *)malloc(sizeof(char) * (i + 1));
	if (fresh == NULL)
		return (fresh);
	i = 0;
	while (s[i] != '\0')
	{
		fresh[i] = f(s[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
