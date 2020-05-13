/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 14:53:36 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/18 16:32:31 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_strjoining(char const *s2, char *fresh, int i)
{
	int j;

	j = 0;
	while (s2[j] != '\0')
	{
		fresh[i] = s2[j];
		i++;
		j++;
	}
	fresh[i] = '\0';
	return (fresh);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*fresh;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	fresh = (char *)malloc(sizeof(char) * (i + j + 1));
	if (fresh == NULL)
		return (fresh);
	ft_bzero(fresh, (i + j + 1));
	if (fresh == NULL)
		return (fresh);
	i = 0;
	while (s1[i] != '\0')
	{
		fresh[i] = s1[i];
		i++;
	}
	fresh = ft_strjoining(s2, fresh, i);
	return (fresh);
}
