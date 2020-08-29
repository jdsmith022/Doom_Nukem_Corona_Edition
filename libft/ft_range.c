/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_range.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:25:54 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:25:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	size_t	i;
	size_t	diff;
	int		*values;

	i = 0;
	if (min >= max)
		return (NULL);
	diff = max - min;
	values = (int *)malloc(diff * sizeof(int));
	while (min != max)
	{
		values[i] = min;
		min++;
		i++;
	}
	return (values);
}
