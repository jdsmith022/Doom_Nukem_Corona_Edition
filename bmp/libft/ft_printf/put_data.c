/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 13:10:43 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 16:22:03 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	get_type(const char *string)
{
	char	type;
	int		i;

	i = 1;
	while (!ft_strchr(PFARG, string[i]))
		i++;
	type = string[i];
	return (type);
}

static	int		get_width(const char *string, va_list ap)
{
	int		i;

	i = 1;
	while (!ft_strchr(PFARG, string[i]))
	{
		if (string[i] == '*' && string[i - 1] != '.')
			return (va_arg(ap, int));
		else if (ft_isdigit(string[i]) && ft_atoi(&string[i]) != 0)
			return (ft_atoi(&string[i]));
		if (string[i] == '.')
			break ;
		i++;
	}
	return (-1);
}

static	int		get_precision(const char *string, va_list ap)
{
	int i;

	i = 1;
	while (!ft_strchr(PFARG, string[i]))
	{
		if (string[i] == '.' && string[i + 1] == '*')
			return (va_arg(ap, int));
		else if (string[i] == '.' && ft_isdigit(string[i + 1]))
			return (ft_atoi(&string[i + 1]));
		else if (string[i] == '.'
		&& (string[i + 1] != '*' && !ft_isdigit(string[i + 1])))
			return (0);
		i++;
	}
	return (-1);
}

static	char	*get_format_string(const char *string)
{
	int		i;
	char	*s;

	i = 1;
	while (!ft_strchr(PFARG, string[i]))
		i++;
	s = ft_strsub(string, 1, i);
	return (s);
}

t_arg			put_data(t_arg arg, const char *s, va_list ap)
{
	arg.format_str = get_format_string(s);
	arg.width = get_width(s, ap);
	arg.precision = get_precision(s, ap);
	arg.type = get_type(s);
	return (arg);
}
