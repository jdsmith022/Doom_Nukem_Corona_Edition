/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_decimal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 17:36:25 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:20:37 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_int_type(t_arg arg)
{
	long long nbr;

	if (arg.flags.h == 0 && arg.flags.l == 0)
		nbr = (int)arg.data;
	else if (arg.flags.h == 1)
		nbr = (short)arg.data;
	else if (arg.flags.h == 2)
		nbr = (signed char)arg.data;
	else if (arg.flags.l == 1)
		nbr = (long)arg.data;
	else
		nbr = (long long)arg.data;
	return (nbr);
}

static void	print_it(long long nbr, t_arg arg, int *print_count, int *max_long)
{
	if (nbr < 0 && arg.precision >= ft_intlen(nbr))
	{
		ft_putchar('-');
		nbr = llabs(nbr);
		*max_long = 1;
	}
	else if (arg.flags.plus == 1 && nbr >= 0 && arg.flags.zero != 1)
		*print_count += ft_putchar('+');
	print_precision(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
	{
		if ((long long)arg.data == LLONG_MIN && *max_long == 1)
		{
			ft_putnbr(922337203685477580);
			ft_putnbr(8);
		}
		else
			ft_putnbr(nbr);
	}
}

static void	print_int(long long nbr, t_arg arg, int *print_count)
{
	int max_long;

	max_long = 0;
	if (arg.flags.space == 1 && nbr >= 0)
		*print_count += ft_putchar(' ');
	if (nbr < 0 && arg.flags.zero == 1)
	{
		*print_count += ft_putchar('-');
		nbr = llabs(nbr);
		max_long = 1;
	}
	else if (nbr >= 0 && arg.flags.zero == 1 && arg.flags.plus == 1)
		*print_count += ft_putchar('+');
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	print_it(nbr, arg, print_count, &max_long);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
		*print_count += ft_intlen(nbr);
}

void		print_decimal(t_arg arg, int *print_count)
{
	print_int(get_int_type(arg), arg, print_count);
}
