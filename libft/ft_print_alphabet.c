/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_alphabet.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:29:06 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:40:41 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_alphabet(void)
{
	char x;

	x = 'a';
	while (x <= 'z')
	{
		ft_putchar(x);
		x++;
	}
}
