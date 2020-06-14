/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 13:43:49 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/13 14:00:05 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && s2[j] != '\0')
	{
		if (s1[i] != s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i++;
		j++;
	}
	if (s1[i] == s2[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
