/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ull_length.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:21:38 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:21:39 by jesmith       ########   odam.nl         */
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
