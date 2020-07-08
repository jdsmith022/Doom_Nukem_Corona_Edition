/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 12:40:21 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 17:22:37 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_modulo(const char *string)
{
	int i;

	i = 1;
	if (string[i] == '%')
		return (1);
	while (!ft_strchr(PFARG, string[i]))
	{
		i++;
		if (string[i] == '%')
			return (1);
	}
	return (0);
}

static	int		count_placeholders(const char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && valid_arg(&str[i]))
		{
			count++;
			i = get_index(str, i);
		}
		i++;
	}
	return (count);
}

static	t_arg	*get_placeholders(const char *string, va_list ap, int size)
{
	t_arg *arg_list;

	arg_list = (t_arg*)ft_memalloc(size * sizeof(t_arg));
	arg_list = get_data_list(string, arg_list, ap);
	return (arg_list);
}

static void		free_args(t_arg *arg_list, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arg_list[i].format_str)
			free(arg_list[i].format_str);
		i++;
	}
	if (arg_list)
		free(arg_list);
}

int				ft_printf(const char *string, ...)
{
	va_list	ap;
	int		size;
	int		print_count;
	t_arg	*arg_list;

	if (!ft_strcmp(string, "%"))
		return (0);
	print_count = 0;
	size = count_placeholders(string);
	va_start(ap, string);
	arg_list = get_placeholders(string, ap, size);
	va_end(ap);
	print_output(arg_list, string, &print_count);
	free_args(arg_list, size);
	return (print_count);
}
