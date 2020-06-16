/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_binary.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 13:21:46 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:20:54 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_binary(t_arg arg, int *print_count)
{
	char *bin_str;

	if (arg.flags.min == 0)
		print_width(arg, print_count);
	if ((long)arg.data == 0)
	{
		*print_count += ft_putchar('0');
		if (arg.flags.min == 1)
			print_width(arg, print_count);
		return ;
	}
	print_precision(arg, print_count);
	bin_str = ft_itoa_base((long)arg.data, 2);
	ft_putstr(bin_str);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
	*print_count += ft_strlen(bin_str);
	free(bin_str);
}
