/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:21:50 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:21:51 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trimlen(const char *s)
{
	size_t i;
	size_t space;
	size_t len;

	len = ft_strlen(s);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	space = i;
	if (s[i] != '\0')
	{
		i = len - 1;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		{
			i--;
			space++;
		}
	}
	return (len - space);
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	size_t	j;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	l = ft_trimlen(s);
	new = ft_memalloc(sizeof(char) * l + 1);
	if (!new)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (j < l)
	{
		new[j] = s[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}
