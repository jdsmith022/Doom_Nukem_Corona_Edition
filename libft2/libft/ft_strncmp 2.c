/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strncmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 13:43:49 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/13 14:21:15 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' && s2[j] != '\0') && i < (n - 1))
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
