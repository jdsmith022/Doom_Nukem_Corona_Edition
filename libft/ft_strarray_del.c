/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarray_del.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 12:04:04 by jesmith        #+#    #+#                */
/*   Updated: 2020/01/08 10:31:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarray_del(char **as)
{
	if (as == NULL || *as == NULL)
		return ;
	ft_strclr(*as);
	free(*as);
	*as = NULL;
}
