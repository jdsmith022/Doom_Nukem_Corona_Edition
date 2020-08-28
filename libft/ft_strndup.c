/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/26 11:52:01 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:23:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < n && s1[i] != '\0')
		i++;
	temp = (char *)malloc(sizeof(char) * (i) + 1);
	if (!temp)
		return (NULL);
	while (j < i)
	{
		temp[k] = s1[j];
		k++;
		j++;
	}
	temp[k] = '\0';
	return (temp);
}
