/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 10:21:29 by jesmith       #+#    #+#                 */
/*   Updated: 2019/02/04 13:25:12 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
