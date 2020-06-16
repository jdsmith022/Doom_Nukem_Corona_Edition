/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arrays.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 18:18:16 by efrank         #+#    #+#                */
/*   Updated: 2019/11/14 12:33:02 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arrays(void **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
