/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 18:13:10 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/16 11:12:21 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int nb;

	nb = n;
	if (nb == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar(n + '0');
	else if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar('-');
		ft_putnbr(nb * -1);
	}
}
