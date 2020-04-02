/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 10:22:37 by jesmith        #+#    #+#                */
/*   Updated: 2020/01/04 13:47:15 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}
