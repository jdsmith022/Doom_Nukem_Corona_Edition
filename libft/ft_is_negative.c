/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_negative.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:24:39 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:39:58 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_is_negative(int n)
{
	if (n >= 0)
		ft_putchar('P');
	else
		ft_putchar('N');
}
