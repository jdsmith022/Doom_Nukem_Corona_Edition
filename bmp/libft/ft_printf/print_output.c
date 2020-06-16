/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 17:12:54 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 17:07:57 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_arg(t_arg arg, int *print_count)
{
	if (arg.type == 's')
		print_string(arg, print_count);
	else if (arg.type == 'c')
		print_char(arg, print_count);
	else if (arg.type == '%')
		print_modulo(arg, print_count);
	else if (arg.type == 'd' || arg.type == 'i')
		print_decimal(arg, print_count);
	else if (arg.type == 'f')
		print_float(arg, print_count);
	else if (ft_tolower(arg.type) == 'x')
		print_hex(arg, print_count);
	else if (arg.type == 'o')
		print_oct(arg, print_count);
	else if (arg.type == 'u')
		print_unsigned(arg, print_count);
	else if (arg.type == 'p')
		print_pointer(arg, print_count);
	else if (arg.type == 'b')
		print_binary(arg, print_count);
}

int		get_index(const char *string, int i)
{
	i++;
	while (!ft_strchr(PFARG, string[i]))
		i++;
	return (i);
}

void	print_output(t_arg *arg_list, const char *string, int *print_count)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (string[i])
	{
		if (string[i] == '%' && valid_arg(&string[i]))
		{
			print_arg(arg_list[x], print_count);
			x++;
			i = get_index(string, i);
		}
		else
			*print_count += ft_putchar(string[i]);
		i++;
	}
}
