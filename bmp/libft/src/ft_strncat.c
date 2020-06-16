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

#include <string.h>

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j] && n > 0)
	{
		s1[i++] = s2[j++];
		n--;
	}
	s1[i] = '\0';
	return (s1);
}
