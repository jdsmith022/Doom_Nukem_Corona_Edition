/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 16:05:18 by fhignett       #+#    #+#                */
/*   Updated: 2019/04/09 16:55:13 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_intlen(long long n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n /= -10;
		len += 2;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
