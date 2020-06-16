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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *fresh;
	char *temp;

	if (!s1 || !s2)
		return (NULL);
	fresh = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	temp = fresh;
	if (!fresh)
		return (NULL);
	ft_strcpy(temp, s1);
	temp += ft_strlen(s1);
	ft_strcpy(temp, s2);
	return (fresh);
}
