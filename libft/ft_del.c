/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_del.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 21:39:07 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:29:44 by jesmith       ########   odam.nl         */
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
