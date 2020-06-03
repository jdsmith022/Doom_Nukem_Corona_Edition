/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rounder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:40:41 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/06/03 12:45:26 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		rounder(double dbl)
{
	int rounded;

	rounded = (int)(dbl + 0.5);
	return (rounded);
}
