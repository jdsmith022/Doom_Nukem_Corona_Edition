/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 12:44:18 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/24 17:03:17 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}
