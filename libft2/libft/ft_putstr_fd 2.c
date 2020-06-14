/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putst_fd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 12:22:36 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/18 12:30:21 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
