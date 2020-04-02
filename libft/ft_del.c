/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_del.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 21:39:07 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/25 11:12:40 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del(void *data, size_t size)
{
	if (data == NULL)
		return ;
	ft_bzero(data, size);
	free(data);
	data = NULL;
	size = 0;
}
