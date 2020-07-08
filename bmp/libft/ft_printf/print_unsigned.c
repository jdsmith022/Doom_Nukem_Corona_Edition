/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_unsigned.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 15:18:17 by efrank         #+#    #+#                */
/*   Updated: 2019/04/15 13:34:39 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_unsigned_type(t_arg arg)
{
	unsigned long long nbr;

	if (arg.flags.h == 0 && arg.flags.l == 0)
		nbr = (unsigned int)arg.data;
	else if (arg.flags.h == 1)
		nbr = (unsigned short)arg.data;
	else if (arg.flags.h == 2)
		nbr = (unsigned char)arg.data;
	else if (arg.flags.l == 1)
		nbr = (unsigned long)arg.data;
	else
		nbr = (unsigned long long)arg.data;
	return (nbr);
}

static void			print_u(unsigned long long nbr, t_arg arg, int *print_count)
{
	if (arg.flags.zero == 1 && arg.flags.plus == 1)
		*print_count += ft_putchar('+');
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	else if (arg.flags.plus == 1 && arg.flags.zero != 1)
		*print_count += ft_putchar('+');
	print_precision(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
		ft_put_unsigned(nbr);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
		*print_count += get_unsignedintlen(nbr);
}

void				print_unsigned(t_arg arg, int *print_count)
{
	print_u(get_unsigned_type(arg), arg, print_count);
}
