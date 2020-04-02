/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 09:34:12 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/11 19:18:46 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == '\0')
		return (0);
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
		if (i == n)
			return (0);
	}
	return ((int)((unsigned char)(s1[i]) - (unsigned char)(s2[i])));
}
