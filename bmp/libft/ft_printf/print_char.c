/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 16:17:15 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/05 18:02:55 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_arg arg, int *print_count)
{
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	*print_count += ft_putchar((char)arg.data);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}

void	print_modulo(t_arg arg, int *print_count)
{
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	*print_count += ft_putchar('%');
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}
