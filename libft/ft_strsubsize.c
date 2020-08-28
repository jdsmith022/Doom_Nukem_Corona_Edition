/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsubsize.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:22:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:22:26 by jesmith       ########   odam.nl         */
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
