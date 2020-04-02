/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stralloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/05 14:36:06 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/08 12:38:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stralloc(const char *s)
{
	return ((char *)malloc(sizeof(char) * ft_strlen(s) + 1));
}
