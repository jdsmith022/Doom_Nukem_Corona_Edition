/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 13:28:38 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:29:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(char *str, int fd)
{
	ft_putstr(str);
	close(fd);
	exit(0);
}
