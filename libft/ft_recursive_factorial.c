/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_recursive_factorial.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:25:43 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:25:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	int x;

	if (nb == 0)
	{
		return (1);
	}
	if ((nb < 0) || (nb >= 32))
	{
		return (0);
	}
	if (nb > 0)
	{
		x = nb;
		return (x * ft_recursive_factorial(nb - 1));
	}
	return (0);
}
