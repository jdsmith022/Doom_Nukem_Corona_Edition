/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_if.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:13:30 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 12:36:46 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_if(char **tab, int (*f)(char*))
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (tab[i] != '\0')
	{
		f(tab[i]);
		if (f(tab[i]) == 1)
			j++;
		i++;
	}
	return ((int)j);
}
