/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_malloc_grid.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/22 17:56:07 by efrank         #+#    #+#                */
/*   Updated: 2019/02/22 17:57:01 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**malloc_grid(int height, int width)
{
	char	**grid;
	int		i;

	i = 0;
	grid = (char **)malloc(sizeof(char *) * height + 1);
	while (i < height)
	{
		grid[i] = malloc(sizeof(char) * width + 1);
		if (!grid[i])
			return (NULL);
		i++;
	}
	grid[i] = NULL;
	return (grid);
}
