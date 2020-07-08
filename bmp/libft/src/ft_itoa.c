/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank        #+#    #+#                 */
/*   Updated: 2019/01/07 18:09:40 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			digcount(int n)
{
	int		len;
	long	divi;

	divi = 1;
	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n / divi)
	{
		divi *= 10;
		len++;
	}
	return (len);
}

char static			*ft_iszero(void)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static long int		ft_isnegative(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char				*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		temp;

	len = digcount(n);
	temp = n;
	if (n == 0)
		return (ft_iszero());
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (n)
	{
		str[len] = ft_isnegative(n % 10) + '0';
		n = ft_isnegative(n / 10);
		len--;
	}
	if (temp < 0)
		str[len] = '-';
	return (str);
}
