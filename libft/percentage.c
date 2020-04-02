/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   percentage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 09:54:58 by jessicasmit    #+#    #+#                */
/*   Updated: 2020/02/02 09:57:12 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double			percentage(t_mlx *mlx, double current)
{
	double placement;
	double distance;

	if (current < mlx->mid)
	{
		placement = current - mlx->min;
		distance = mlx->mid - mlx->min;
	}
	else
	{
		placement = current - mlx->mid;
		distance = mlx->max - mlx->mid;
	}
	return ((distance == 0) ? 1.0 : (placement / distance));
}