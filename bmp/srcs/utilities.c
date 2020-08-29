/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:18:30 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 22:17:32 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void				exit_with_error(t_bmp *bmp, const char *message)
{
	bmp = NULL;
	ft_putstr_fd(message, 2);
}
