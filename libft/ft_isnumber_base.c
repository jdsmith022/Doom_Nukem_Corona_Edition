/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber_base.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:31:24 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:31:25 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_isnumber_base(char *str, int base)
{
	size_t		index;
	size_t		digits;

	index = 0;
	digits = 0;
	while (ft_iswhitespace(str[index]))
		index++;
	if (base != 10 && ft_has_prefix(&str[index], base) == 0)
		return (0);
	if (base == 2 || base == 16)
		index += 2;
	else if (base == 8)
		index++;
	else if (base == 10 && (str[index] == '-' || str[index] == '+'))
		index++;
	while (ft_isdigit_base(str[index], base) >= 0 && str[index])
	{
		index++;
		digits++;
	}
	if (str[index] == '\0' && digits)
		return (1);
	return (0);
}
