/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 19:06:48 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/19 12:35:41 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		l;
	char	*trim;

	j = 0;
	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	l = 0;
	while (s[j] == ' ' | s[j] == '\t' | s[j] == '\n')
		j++;
	while (i > 0 && (s[i - 1] == ' ' | s[i - 1] == '\t' |
			s[i - 1] == '\n') && s[j] != '\0')
		i--;
	trim = (char *)ft_memalloc(sizeof(char) * (i - j) + 1);
	if (trim == NULL)
		return (NULL);
	while (j != i)
	{
		trim[l] = s[j];
		l++;
		j++;
	}
	return (trim);
}
