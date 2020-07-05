/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rounder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 14:34:28 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/05 14:35:42 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_rounder(double dbl)
{
	int rounded;

	rounded = (int)(dbl + 0.5);
	return (rounded);
}
