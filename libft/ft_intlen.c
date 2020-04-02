/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/29 16:38:51 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/11 19:28:51 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return ((int)i);
}
