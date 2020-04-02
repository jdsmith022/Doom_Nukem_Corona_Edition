/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:19:04 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 13:46:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int x;

	x = 1;
	if (nb < 0)
		return (0);
	if (nb == 0)
		return (0);
	while (x * x != nb)
	{
		x++;
		if (x * x == nb)
			return (x);
		else if (x * x > nb)
			return (0);
	}
	return (0);
}
