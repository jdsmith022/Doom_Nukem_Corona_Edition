/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 13:48:03 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/17 14:26:44 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (s == NULL || *f == NULL)
		return ;
	while (*s)
	{
		f(s);
		s++;
	}
}
