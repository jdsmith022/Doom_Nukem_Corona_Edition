/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 15:20:28 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:29:57 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int neg;
	int result;

	neg = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
		if (*str == '+')
			return (0);
	}
	if (*str == '+')
		str++;
	while (*str != 0 && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * neg);
}
