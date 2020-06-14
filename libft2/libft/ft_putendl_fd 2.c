/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <nde-wild@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 12:25:05 by nde-wild       #+#    #+#                */
/*   Updated: 2019/04/01 08:30:22 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
