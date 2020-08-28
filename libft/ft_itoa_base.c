/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 13:24:13 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:28:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, int base)
{
	char	*result;
	int		neg;
	size_t	i;

	i = 0;
	neg = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = (char *)malloc(ft_intlen(n) + 1);
	if (result == NULL)
		return (NULL);
	if (n < 0)
		n = -n;
	if (n == 0)
		result[i] = '0';
	while (n > 0)
	{
		result[i] = (n % base) + '0';
		n = n / base;
		i++;
	}
	if (neg < 0)
		result[i] = '-';
	result[ft_intlen(neg)] = '\0';
	return (ft_strrev(result));
}
