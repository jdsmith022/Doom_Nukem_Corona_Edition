/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put_unsigned.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 13:20:29 by efrank         #+#    #+#                */
/*   Updated: 2019/04/12 13:21:47 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_put_unsigned(unsigned long long n)
{
	unsigned long long nb;

	nb = n;
	if (nb < 10)
		ft_putchar(nb + 48);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
