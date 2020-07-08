/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_length.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 16:12:34 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:18:31 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_float_length(long double num, int precision)
{
	int length;

	if (!num)
		return (1);
	length = 0;
	length += ft_intlen(num);
	if (!precision)
		return (length);
	else if (precision != -1)
		length += precision + 1;
	return (length);
}

int		get_hex_length(unsigned long long num)
{
	char	*hex;
	int		len;

	if (!num)
		return (1);
	hex = ft_itoa_base(num, 16);
	len = ft_strlen(hex);
	free(hex);
	return (len);
}

int		get_pointer_length(unsigned long long num)
{
	char	*pointer;
	int		len;

	if (!num)
		return (1);
	pointer = ft_itoa_base(num, 16);
	len = ft_strlen(pointer);
	free(pointer);
	return (len);
}

int		get_oct_length(unsigned long long num)
{
	char	*oct;
	int		len;

	if (!num)
		return (1);
	oct = ft_itoa_base(num, 8);
	len = ft_strlen(oct);
	free(oct);
	return (len);
}

int		get_unsignedintlen(unsigned long long n)
{
	int len;

	if (!n)
		return (1);
	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
