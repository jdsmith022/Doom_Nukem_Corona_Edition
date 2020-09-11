/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:28:54 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static void		log_sprite_error(uint8_t type)
{
	ft_putstr("sprite ");
	ft_putnbr(type);
	ft_putstr(" not found\n");
}

void			set_sprite(t_doom *doom, uint8_t type, t_item *item)
{
	uint16_t	i;

	i = 0;
	item->sprite = NULL;
	while (i < doom->lib.len_obj_lib)
	{
		if (!doom->lib.obj_lib[i])
			break ;
		else if (*((uint8_t *)doom->lib.obj_lib[i]->userdata) == type)
		{
			item->sprite = doom->lib.obj_lib[i];
			return ;
		}
		i++;
	}
	log_sprite_error(type);
	return ;
}
