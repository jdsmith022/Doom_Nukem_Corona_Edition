/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 16:16:56 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 17:58:29 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(t_arg arg, int *print_count)
{
	int		i;
	char	*s;

	i = 0;
	s = (char*)arg.data;
	if (!s)
		s = "(null)";
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	while (s[i])
	{
		if (arg.precision >= 0 && i >= arg.precision)
			break ;
		*print_count += ft_putchar(s[i]);
		i++;
	}
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}
