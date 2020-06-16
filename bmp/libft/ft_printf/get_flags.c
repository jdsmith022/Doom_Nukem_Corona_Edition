/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_flags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 13:47:32 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/15 14:00:49 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_hash(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

static int		check_l(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_tolower(s[i]) == 'l')
		{
			if (s[i + 1] == 'l')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		check_h(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'h')
		{
			if (s[i + 1] == 'h')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

static t_flags	set_flags(t_arg arg)
{
	t_flags flags;

	flags = put_flags(arg);
	flags.hashtag = check_hash(arg.format_str);
	flags.l = check_l(arg.format_str);
	flags.h = check_h(arg.format_str);
	return (flags);
}

void			get_flags(t_arg *arg_list, int i)
{
	arg_list[i].flags = set_flags(arg_list[i]);
}
