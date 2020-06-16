/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:22:04 by efrank         #+#    #+#                */
/*   Updated: 2019/04/19 14:17:28 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	round_zero_precision(double num)
{
	double temp;

	temp = num - (long)num;
	if (temp >= 0.5)
		ft_putnbr((long)num + 1);
	else
		ft_putnbr((long)num);
	return (1);
}

static void	round_string(char *string, long double *num)
{
	size_t	len;
	int		i;

	len = ft_strlen(string);
	i = len;
	if (string[i - 1] > '5')
	{
		while (string[i - 2] == '9')
		{
			string[i - 2] = '0';
			if (i - 2 == 0)
				*num += 1;
			i--;
		}
		string[i - 2] += 1;
	}
	string[len - 1] = '\0';
}

static char	*get_after_dot(double temp, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char*)malloc(sizeof(char) * len + 1);
	while (i <= len)
	{
		temp *= 10;
		result[i] = (long long)temp + '0';
		i++;
		temp -= (long long)temp;
	}
	result[i] = '\0';
	return (result);
}

static void	ft_putfloat(long double num, t_arg arg, int *print_count)
{
	char		*after_dot;
	long double	temp;

	if (num < 0 && arg.flags.min != 1)
	{
		*print_count += ft_putchar('-');
		num = fabsl(num);
	}
	if (!arg.precision)
	{
		*print_count += round_zero_precision(num);
		return ;
	}
	temp = num - (long long)num;
	after_dot = get_after_dot(temp, arg.precision);
	round_string(after_dot, &num);
	ft_putnbr((long long)num);
	*print_count += ft_intlen((long long)num);
	*print_count += ft_putchar('.');
	ft_putstr(after_dot);
	*print_count += ft_strlen(after_dot);
	free(after_dot);
}

void		print_float(t_arg arg, int *print_count)
{
	long double nbr;

	if (arg.flags.l == 0)
		nbr = arg.dbl;
	else
		nbr = arg.ldbl;
	if (arg.precision == -1)
		arg.precision = 6;
	if (arg.flags.space == 1 && nbr >= 0)
		*print_count += ft_putchar(' ');
	if (nbr < 0 && arg.flags.zero == 1 && arg.flags.l != 1)
		*print_count += ft_putchar('-');
	else if (nbr >= 0 && arg.flags.zero == 1 && arg.flags.plus == 1)
		*print_count += ft_putchar('+');
	if (arg.flags.min == 0)
		print_width(arg, print_count);
	if (nbr >= 0 && arg.flags.zero != 1 && arg.flags.plus == 1)
		*print_count += ft_putchar('+');
	ft_putfloat(nbr, arg, print_count);
	if (arg.flags.min == 1)
		print_width(arg, print_count);
}
