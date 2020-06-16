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

static size_t	count_whitesp(const char *s)
{
	size_t count;
	size_t i;

	i = 0;
	count = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		count++;
	}
	if (!s[i])
		return (count);
	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		count++;
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	char	*trimmed;
	size_t	ws;
	size_t	len;

	if (!s)
		return (NULL);
	ws = count_whitesp(s);
	len = ft_strlen(s) - ws;
	trimmed = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	while (*s == '\n' || *s == '\t' || *s == ' ')
		s++;
	ft_strncpy(trimmed, s, len);
	trimmed[len] = '\0';
	return (trimmed);
}
