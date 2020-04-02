/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsubsize.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 10:28:10 by jesmith        #+#    #+#                */
/*   Updated: 2019/02/21 13:47:19 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsubsize(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}
