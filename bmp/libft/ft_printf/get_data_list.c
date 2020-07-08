/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 17:09:01 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 17:07:16 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_arg	check_float_data(t_arg arg, va_list ap)
{
	if (arg.type == 'f')
	{
		if (arg.flags.l == 0)
			arg.dbl = va_arg(ap, double);
		else
			arg.ldbl = va_arg(ap, long double);
	}
	else
		arg.data = va_arg(ap, void*);
	return (arg);
}

int				valid_arg(const char *s)
{
	int i;

	i = 1;
	while (s[i] && !ft_strchr(PFARG, s[i]))
		i++;
	if (s[i] && ft_strchr(PFARG, s[i]))
		return (1);
	return (0);
}

t_arg			*get_data_list(const char *string, t_arg *arg_list, va_list ap)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (string[i])
	{
		if (string[i] == '%' && valid_arg(&string[i]))
		{
			arg_list[x] = put_data(arg_list[x], &string[i], ap);
			get_flags(arg_list, x);
			if (!check_modulo(&string[i]))
				arg_list[x] = check_float_data(arg_list[x], ap);
			i = get_index(string, i);
			x++;
		}
		i++;
	}
	return (arg_list);
}
