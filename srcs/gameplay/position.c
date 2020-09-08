/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   position.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:28:42 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

SDL_Rect		get_position(uint16_t index, int start_x, int start_y)
{
	SDL_Rect	position;

	position.x = start_x;
	position.y = start_y + (index * 55);
	position.w = 20;
	position.h = 30;
	return (position);
}

void			set_positions(t_list **basket)
{
	t_list		*temp;
	t_item		*item;
	uint16_t	i;

	i = 0;
	temp = *basket;
	if (!temp)
		return ;
	while (temp)
	{
		item = (t_item *)temp->content;
		item->position = get_position(i, 20, 60);
		temp = temp->next;
		i++;
	}
}
