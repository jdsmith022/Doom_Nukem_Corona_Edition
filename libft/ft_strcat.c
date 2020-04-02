/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 15:58:41 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/08 12:48:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *src1, const char *src2)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (src1[i] != '\0')
		i++;
	while (src2[j] != '\0')
	{
		src1[i] = src2[j];
		i++;
		j++;
	}
	src1[i] = 0;
	return (src1);
}
