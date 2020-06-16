/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 15:51:46 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 12:37:14 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_hex_type(t_arg arg)
{
	unsigned long long nbr;

	if (arg.flags.h == 0 && arg.flags.l == 0)
		nbr = (unsigned int)arg.data;
	else if (arg.flags.h == 1)
		nbr = (unsigned short)arg.data;
	else if (arg.flags.h == 2)
		nbr = (unsigned char)arg.data;
	else if (arg.flags.l == 1)
		nbr = (unsigned long)arg.data;
	else
		nbr = (unsigned long long)arg.data;
	return (nbr);
}

static	void		hex_hashtag(t_arg arg, int *print_count)
{
	*print_count += ft_putchar('0');
	if (arg.type == 'X')
		*print_count += ft_putchar('X');
	else
		*print_count += ft_putchar('x');
}

static void            put_hex(unsigned long long nbr, char *s, char t, int *c)
{
    int i;

    i = 0;
    s = ft_itoa_base(nbr, 16);
    while (s[i])
    {
        if (t == 'X')
            *c += ft_putchar(ft_toupper(s[i]));
        else
            *c += ft_putchar(s[i]);
        i++;
    }
    if (s)
        free(s);
}

static void			print_h(unsigned long long nbr, t_arg arg, int *print_count)
{
	char *hex_string;

	hex_string = NULL;
	if (!nbr && arg.precision != 0)
	{
		nbr_zero(arg, print_count);
		return ;
	}
	if (arg.flags.hashtag == 1 && arg.flags.zero == 1 && nbr != 0)
		hex_hashtag(arg, print_count);
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	if (arg.flags.hashtag == 1 && arg.flags.zero == 0 && nbr != 0)
		hex_hashtag(arg, print_count);
	print_precision(arg, print_count);
	if (nbr != 0 || arg.precision != 0)
		put_hex(nbr, hex_string, arg.type, print_count);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}

void				print_hex(t_arg arg, int *print_count)
{
	print_h(get_hex_type(arg), arg, print_count);
}
