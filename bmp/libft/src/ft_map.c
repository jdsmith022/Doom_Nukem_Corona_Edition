/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 14:58:28 by efrank         #+#    #+#                */
/*   Updated: 2019/11/14 12:34:07 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_map(double n, double a, double b, double y, double z)
{
	return ((n - a) * (z - y) / (b - a) + y);
}
