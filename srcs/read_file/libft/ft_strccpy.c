/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 13:27:10 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/21 13:31:41 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strccpy(void *dst, void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*source;

	dest = dst;
	source = src;
	i = 0;
	while (i < n)
	{
		if (*source == (unsigned char)c || *source == '\0')
		{
			*dest = '\0';
			return (&dst[0]);
		}
		*dest = *source;
		i++;
		dest++;
		source++;
	}
	return (0);
}
