/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ull_length.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 12:41:13 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/06 12:43:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_ull_length(unsigned long long num, unsigned int base)
{
	unsigned int length;

	length = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		length++;
	}
	return (length);
}
