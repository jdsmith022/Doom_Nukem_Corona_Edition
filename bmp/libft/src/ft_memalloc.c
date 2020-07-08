/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank        #+#    #+#                 */
/*   Updated: 2019/01/07 18:09:40 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void			*mem;
	unsigned char	*cpy;
	size_t			i;

	i = 0;
	mem = malloc(size);
	cpy = (unsigned char *)mem;
	if (!mem)
		return (NULL);
	while (i < size)
	{
		cpy[i] = 0;
		i++;
	}
	return (mem);
}
