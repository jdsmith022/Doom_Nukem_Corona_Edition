/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 12:27:14 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/17 18:55:24 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_pixel(t_mlx *mlx, int color, int x, int y)
{
	size_t	index;

	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	{
		index = (y * mlx->size_line) + (x * mlx->bits_ppixel / 8);
		mlx->addr_str[index] = color;
		index++;
		mlx->addr_str[index] = color >> 8;
		index++;
		mlx->addr_str[index] = color >> 16;
	}
}
