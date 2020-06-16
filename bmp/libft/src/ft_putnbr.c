/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 13:01:01 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	long num;

	num = n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar('-');
	}
	if (num >= 0 && num <= 9)
		ft_putchar(num + '0');
	if (num > 9)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
}
