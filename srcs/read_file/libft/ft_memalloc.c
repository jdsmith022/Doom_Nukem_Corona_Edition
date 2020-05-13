/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 18:55:51 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/21 19:02:30 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (0);
	ft_memset(str, 0, size);
	return (str);
}
