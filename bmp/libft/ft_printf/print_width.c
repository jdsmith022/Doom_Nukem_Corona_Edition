/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_width.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 15:37:32 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/19 14:19:09 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void		put_hexwidth(t_arg arg, char c, int *print_count)
{
	int	len;

	len = get_hex_length((unsigned int)arg.data);
	if (arg.precision > 0 && arg.precision > len)
		len = arg.precision;
	if (arg.flags.hashtag == 1 && (int)arg.data != 0)
		len += 2;
	if ((int)arg.data == 0 && arg.precision >= 0)
		len = arg.precision;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

static	void		put_octwidth(t_arg arg, char c, int *print_count)
{
	int	len;

	len = get_oct_length((unsigned int)arg.data);
	if (arg.precision > 0 && arg.precision > len)
		len = arg.precision;
	if (arg.flags.hashtag == 1 && arg.flags.zero == 0
	&& (int)arg.data != 0)
		len += 1;
	if (arg.flags.hashtag != 1 && (int)arg.data == 0
	&& arg.precision == 0)
		len = 0;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

static	void		put_pointerwidth(t_arg arg, char c, int *print_count)
{
	int	len;

	if (!arg.data)
		len = 3;
	else
		len = get_pointer_length((unsigned long long)arg.data) + 2;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

static	void		put_binarywidth(t_arg arg, char c, int *print_count)
{
	int		len;

	len = ft_strlen(ft_itoa_base((long)arg.data, 2));
	if (arg.precision > 0 && arg.precision > len)
		len = arg.precision;
	while (len < arg.width)
	{
		*print_count += ft_putchar(c);
		len++;
	}
}

void				print_width(t_arg arg, int *print_count)
{
	char c;

	c = ' ';
	if (arg.width <= 0)
		return ;
	if (arg.flags.zero == 1)
		c = '0';
	if (arg.type == 's')
		put_strwidth(arg, c, print_count);
	else if (arg.type == 'c' || arg.type == '%')
		put_charwidth(arg, c, print_count);
	else if (arg.type == 'd' || arg.type == 'i')
		put_intwidth(arg, c, print_count);
	else if (arg.type == 'u')
		put_unsignedwidth(arg, c, print_count);
	else if (arg.type == 'f')
		put_floatwidth(arg, c, print_count);
	else if (ft_tolower(arg.type) == 'x')
		put_hexwidth(arg, c, print_count);
	else if (arg.type == 'o')
		put_octwidth(arg, c, print_count);
	else if (arg.type == 'p')
		put_pointerwidth(arg, c, print_count);
	else if (arg.type == 'b')
		put_binarywidth(arg, c, print_count);
}
