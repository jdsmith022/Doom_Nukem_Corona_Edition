/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_width_extra.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 13:28:06 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/16 18:02:54 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_strwidth(t_arg arg, char c, int *print_count)
{
	int		i;
	int		len;
	char	*s;

	i = arg.width;
	s = (char*)arg.data;
	len = 0;
	if (!s)
		len = 6;
	else
		len = ft_strlen(s);
	if (arg.precision > 0 && arg.precision < len)
		len = arg.precision;
	else if (arg.precision == 0)
		len = 0;
	while (i > len)
	{
		*print_count += ft_putchar(c);
		i--;
	}
}

void		put_charwidth(t_arg arg, char c, int *print_count)
{
	int i;

	i = arg.width;
	while (i > 1)
	{
		*print_count += ft_putchar(c);
		i--;
	}
}

void		put_unsignedwidth(t_arg arg, char c, int *print_count)
{
	int					len;
	unsigned long long	nbr;

	nbr = get_unsigned_type(arg);
	len = get_unsignedintlen(nbr);
	if (arg.precision > 0 && arg.precision > len)
		len += (arg.precision - len);
	if (arg.flags.space == 1 || arg.flags.plus == 1)
		len++;
	if (nbr == 0 && arg.precision == 0)
		len = 0;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

void		put_intwidth(t_arg arg, char c, int *print_count)
{
	int			len;
	long long	nbr;

	nbr = get_int_type(arg);
	len = ft_intlen(nbr);
	if (arg.precision > 0 && arg.precision > len)
		len += (arg.precision - len);
	if ((arg.flags.space == 1 || arg.flags.plus == 1) && nbr >= 0)
		len++;
	else if (nbr < 0 && arg.precision > len - 1)
		len++;
	if (nbr == 0 && arg.precision == 0)
		len = 0;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

void		put_floatwidth(t_arg arg, char c, int *print_count)
{
	int len;

	len = 0;
	if (arg.precision >= 0)
	{
		if (arg.precision == 0)
			len = arg.width - 1;
		else
			len = arg.width - get_float_length(arg.dbl, arg.precision);
	}
	if (arg.dbl >= 0 && arg.flags.plus == 1)
		len--;
	while (len > 0)
	{
		*print_count += ft_putchar(c);
		len--;
	}
}
