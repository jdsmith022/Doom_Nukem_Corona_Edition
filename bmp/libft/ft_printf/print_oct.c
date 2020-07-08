/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_oct.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 17:19:20 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/19 14:18:45 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		nbr_zero(t_arg arg, int *print_count)
{
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	print_precision(arg, print_count);
	*print_count += ft_putchar('0');
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}

static void	put_oct(unsigned long long nbr, t_arg arg, int *print_count)
{
	char *oct_string;

	oct_string = NULL;
	if (!nbr && arg.precision != 0)
	{
		nbr_zero(arg, print_count);
		return ;
	}
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	if (arg.flags.hashtag == 1 && arg.flags.zero == 0
	&& arg.precision < (get_oct_length(nbr) + 1))
		*print_count += ft_putchar('0');
	print_precision(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
	{
		oct_string = ft_itoa_base(nbr, 8);
		ft_putstr(oct_string);
		*print_count += ft_strlen(oct_string);
	}
	if (arg.flags.min == 1)
		print_width(arg, print_count);
	if (oct_string)
		free(oct_string);
}

void		print_oct(t_arg arg, int *print_count)
{
	put_oct(get_unsigned_type(arg), arg, print_count);
}
