/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 16:54:51 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/18 19:02:35 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char			*str;
	size_t			i;
	size_t			len;
	unsigned int	bignum;

	i = 0;
	len = (size_t)ft_intsize(n);
	str = (char*)ft_memalloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		bignum = -n;
		i++;
	}
	else
		bignum = n;
	while (len > i)
	{
		str[len - 1] = bignum % 10 + '0';
		bignum /= 10;
		len--;
	}
	return (str);
}
