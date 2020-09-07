/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp_safe_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 11:09:44 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 11:10:17 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

void			bmp_safe_exit(t_doom *doom, t_bmp *images)
{
	doom_exit_lib_failure(images, MALLOC_ERR);
	doom_exit_failure(doom, "error: bmp reader");
}
