/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_div_mod.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:22:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:39:36 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	int x;
	int y;

	x = a / b;
	*div = x;
	y = a % b;
	*mod = y;
}
