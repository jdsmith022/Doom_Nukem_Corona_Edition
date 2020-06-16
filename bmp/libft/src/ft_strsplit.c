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

static int		count_words(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char		**malloc_words(const char *s, char c, int word_count)
{
	int		i;
	int		j;
	int		count;
	char	**words;

	count = 0;
	i = 0;
	j = 0;
	if (!(words = (char **)malloc(sizeof(char *) * word_count + 1)))
		return (NULL);
	while (s[j] == c)
		j++;
	while (i < word_count)
	{
		while (s[j] != c && s[j++] != '\0')
			count++;
		while (s[j] == c)
			j++;
		if (!(words[i] = (char *)malloc(sizeof(char) * count + 1)))
			return (NULL);
		count = 0;
		i++;
	}
	words[i] = NULL;
	return (words);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**word_arr;

	i = 0;
	j = 0;
	k = 0;
	if (!s)
		return (NULL);
	word_arr = malloc_words(s, c, count_words(s, c));
	if (!word_arr)
		return (NULL);
	while (i < count_words(s, c))
	{
		while (s[k] == c)
			k++;
		while (s[k] && s[k] != c)
			word_arr[i][j++] = s[k++];
		word_arr[i][j] = '\0';
		j = 0;
		i++;
	}
	return (word_arr);
}
