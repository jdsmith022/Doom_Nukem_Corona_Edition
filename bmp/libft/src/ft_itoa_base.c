/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/25 21:27:11 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/04/19 13:05:36 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		len_size(unsigned long long nb, int base)
{
	int len;

	len = 0;
	while (nb > 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

char			*ft_itoa_base(unsigned long long nb, int base)
{
	int					len;
	unsigned long long	nbr;
	char				*str;

	if (base < 2 || base > 16)
		return (NULL);
	nbr = (long)nb;
	if (!nbr)
		return ("0");
	len = len_size(nbr, base);
	str = (char*)malloc(sizeof(char) * len + 1);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = "0123456789abcdef"[nbr % base];
		nbr /= base;
		if (str[len] == '-')
			break ;
	}
	return (str);
}
