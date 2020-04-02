/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mminkjan <mminkjan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 18:47:24 by mminkjan       #+#    #+#                */
/*   Updated: 2020/02/17 18:54:13 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int		mlx_exit(char *s)
{
	ft_putstr(s);
	// ft_bzero(mlx, sizeof(t_mlx));
	exit(EXIT_SUCCESS);
	return (0);
}