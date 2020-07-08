/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 11:41:43 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/15 11:48:54 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_plus(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

static int		check_min(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

static int		check_zero(char *s, int min, t_arg arg)
{
	int i;

	i = 0;
	if (min == 1)
		return (0);
	if (arg.type != 'f' && arg.precision != -1)
		return (0);
	while (s[i])
	{
		if (s[i] == '.')
			return (0);
		if (ft_isdigit(s[i]))
		{
			if (s[i] == '0')
				return (1);
			else
			{
				while (ft_isdigit(s[i]))
					i++;
			}
		}
		else
			i++;
	}
	return (0);
}

static int		check_space(char *s, int plus)
{
	int i;

	i = 0;
	if (plus == 1)
		return (0);
	while (s[i])
	{
		if (s[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

t_flags			put_flags(t_arg arg)
{
	t_flags flags;

	flags.min = check_min(arg.format_str);
	flags.plus = check_plus(arg.format_str);
	flags.zero = check_zero(arg.format_str, flags.min, arg);
	flags.space = check_space(arg.format_str, flags.plus);
	return (flags);
}
