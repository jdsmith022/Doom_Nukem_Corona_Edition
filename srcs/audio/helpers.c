/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:27:36 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/audio.h"

void				exit_error(t_doom *doom, const char *message)
{
	ft_putstr_fd(message, 2);
	doom_exit_failure(doom, "error: audio lib");
}
