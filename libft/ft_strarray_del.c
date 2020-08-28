/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarray_del.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:25:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:25:16 by jesmith       ########   odam.nl         */
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
