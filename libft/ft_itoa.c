/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 09:53:18 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:28:02 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
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
		result[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	if (neg < 0)
		result[i] = '-';
	result[ft_intlen(neg)] = '\0';
	return (ft_strrev(result));
}
