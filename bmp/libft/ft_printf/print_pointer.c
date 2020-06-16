/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_pointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 16:51:40 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:19:43 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		no_pointer(t_arg arg, int *print_count)
{
	if (!arg.flags.min)
		print_width(arg, print_count);
	if (arg.precision == 0)
	{
		ft_putstr("0x");
		*print_count += 2;
	}
	else
	{
		ft_putstr("0x0");
		*print_count += 3;
	}
	if (arg.flags.min)
		print_width(arg, print_count);
}

void			print_pointer(t_arg arg, int *print_count)
{
	char *hex_num;

	if (!arg.data)
	{
		no_pointer(arg, print_count);
		return ;
	}
	hex_num = ft_itoa_base((unsigned long long)arg.data, 16);
	if (!arg.flags.min)
		print_width(arg, print_count);
	ft_putstr("0x");
	ft_putstr(hex_num);
	*print_count += ft_strlen(hex_num) + 2;
	if (arg.flags.min)
		print_width(arg, print_count);
	free(hex_num);
}
