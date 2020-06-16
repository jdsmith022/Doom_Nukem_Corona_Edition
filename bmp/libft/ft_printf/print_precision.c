/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_precision.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 12:41:57 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:21:35 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	binary_precision(t_arg arg)
{
	char	*bin;
	int		count;

	bin = ft_itoa_base((long)arg.data, 2);
	count = arg.precision - ft_strlen(bin);
	free(bin);
	return (count);
}

void		print_precision(t_arg arg, int *print_count)
{
	int count;

	count = 0;
	if (arg.type == 'd' || arg.type == 'i')
	{
		count = arg.precision - ft_intlen(ABS(get_int_type(arg)));
		if ((long long)arg.data == LONG_MIN && arg.flags.l != 0
		&& arg.flags.h != 0)
			count++;
	}
	else if (ft_tolower(arg.type) == 'x')
		count = arg.precision - get_hex_length((int)arg.data);
	else if (arg.type == 'o')
		count = arg.precision - get_oct_length((int)arg.data);
	else if (arg.type == 'u')
		count = arg.precision - get_unsignedintlen((unsigned int)arg.data);
	else if (arg.type == 'b')
		count = binary_precision(arg);
	while (count > 0)
	{
		*print_count += ft_putchar('0');
		count--;
	}
}
