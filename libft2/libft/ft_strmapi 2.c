/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:12:14 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/17 16:37:34 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	unsigned int	i;

	if (s == NULL || *f == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	fresh = (char *)malloc(sizeof(char) * (i + 1));
	if (fresh == NULL)
		return (fresh);
	i = 0;
	while (s[i] != '\0')
	{
		fresh[i] = f(i, s[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
