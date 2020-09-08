/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stop_sounds.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:27:48 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/audio.h"

void	stop_sounds(void)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}
