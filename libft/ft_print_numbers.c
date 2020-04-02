/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:28:00 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:28:21 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_numbers(void)
{
	char x;

	x = '0';
	while (x <= '9')
	{
		ft_putchar(x);
		x++;
	}
}
