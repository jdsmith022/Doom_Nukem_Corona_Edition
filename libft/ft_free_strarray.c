/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_strarray.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 10:16:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:29:27 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_strarray(char **alt_values)
{
	size_t index;

	index = 0;
	while (alt_values[index])
	{
		ft_bzero(alt_values[index], 1);
		free(alt_values[index]);
		index++;
	}
	if (alt_values != NULL)
		free(alt_values);
}
