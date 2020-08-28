/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:21:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:21:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_arrayalloc(const char *str, char c,
					int *index, char **array_strs)
{
	char	*char_string;
	size_t	index_2;
	int		diff_index;

	index_2 = 0;
	diff_index = *index;
	while (diff_index != c && str[diff_index])
		diff_index++;
	char_string = (char *)malloc(sizeof(char_string) * (diff_index - *index));
	if (char_string == NULL)
	{
		ft_strdel(char_string);
		ft_free_strarray(array_strs);
		return (NULL);
	}
	while (str[*index] != c && str[*index])
	{
		char_string[index_2] = str[*index];
		index_2++;
		*index = *index + 1;
	}
	char_string[index_2] = '\0';
	return (char_string);
}

static size_t	ft_wrdscount(char const *s, char c)
{
	size_t index;
	size_t word;

	index = 0;
	word = 0;
	if (!s)
		return (0);
	while (s[index] == c)
		index++;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index] != '\0')
			word++;
		index++;
	}
	if (s[0] != '\0')
		word++;
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	size_t	array_dex;
	int		index;
	size_t	numofparts;

	index = 0;
	array_dex = 0;
	if (s == NULL)
		return (NULL);
	numofparts = ft_wrdscount(s, c);
	array = (char**)malloc(sizeof(char *) * numofparts + 1);
	if (array == NULL)
		return (NULL);
	while (s[index] == c && s[index])
		index++;
	while (array_dex < numofparts && s[index])
	{
		array[array_dex] = ft_arrayalloc(s, c, &index, array);
		array_dex++;
		while (s[index] == c && s[index])
			index++;
	}
	array[array_dex] = 0;
	return (array);
}
