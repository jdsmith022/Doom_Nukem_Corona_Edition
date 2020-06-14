/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnequ.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 12:55:23 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/24 17:09:52 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	if (n == 0)
		return (1);
	while (s1[i] == s2[i])
	{
		if ((s1[i] == '\0' && s2[i] == '\0') || i == (n - 1))
			return (1);
		i++;
	}
	return (0);
}
