/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 13:34:57 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/19 13:47:08 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_arrayfree(char *array, int i)
{
	free(array);
	i++;
	return (i);
}

static int	reset(char const **s, int i)
{
	while (i > 1)
	{
		i--;
		*s = *s + 1;
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char			**array;
	unsigned int	i;
	int				j;

	i = 1;
	j = 0;
	if (s == NULL)
		return (NULL);
	array = (char **)ft_memalloc(sizeof(char*) * (ft_wordcount(s, c) + 1));
	if (!array)
		return (NULL);
	while (*s != '\0' && ft_wordcount(s, c) != 0)
	{
		while (*s == c)
			s++;
		array[j] = ft_strnew(i);
		if (ft_strccpy(array[j], (void*)s, c, i) == 0)
			i = ft_arrayfree(array[j], i);
		else
		{
			i = reset(&s, i);
			j++;
		}
	}
	return (array);
}
