#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

SDL_Rect		get_position(uint16_t index, int start_x, int start_y)
{
	SDL_Rect	position;

	position.x = start_x;
	position.y = start_y + (index * 55);
	position.w = 30;
	position.h = 30;
	return position;
}

void			set_positions(t_list **basket)
{
	t_list		*temp;
	t_item		*item;
	uint16_t	i;

	i = 0;
	temp = *basket;
	if (!temp)
		return;
	while (temp)
	{
		item = (t_item *)temp->content;
		item->position = get_position(i, 35, 60);
		temp = temp->next;
		i++;
	}
}
