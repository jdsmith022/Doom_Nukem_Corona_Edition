/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:26:30 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:26:31 by jesmith       ########   odam.nl         */
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
