/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_alphabet.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:26:37 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:26:37 by jesmith       ########   odam.nl         */
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
