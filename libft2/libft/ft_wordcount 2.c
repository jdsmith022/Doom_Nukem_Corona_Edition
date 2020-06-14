/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wordcount.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 13:20:34 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/21 13:25:59 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount(const char *s, char c)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			w++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (w);
}
