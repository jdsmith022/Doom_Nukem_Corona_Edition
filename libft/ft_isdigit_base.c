/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit_base.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 10:12:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:30:57 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isdigit_base(char c, int base)
{
	const char	*digits;
	int			index;

	digits = "0123456789ABCDEF";
	index = 0;
	while (index < base)
	{
		if (digits[index] == ft_toupper(c))
			return (index);
		index++;
	}
	return (-1);
}
