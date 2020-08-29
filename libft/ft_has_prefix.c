/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_has_prefix.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 10:14:56 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:29:22 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_prefix(const char *str, int base)
{
	size_t	index;

	index = 0;
	if (base == 2 || base == 8 || base == 16)
	{
		if (str[index] != '0')
			return (0);
		index++;
		if (base == 2 && (str[index] == 'b' || str[index] == 'B'))
			return (1);
		if (base == 16 && (str[index] == 'x' || str[index] == 'X'))
			return (1);
		if (base == 8)
			return (1);
	}
	return (0);
}
