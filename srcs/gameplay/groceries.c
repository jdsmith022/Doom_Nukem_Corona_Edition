#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/events.h"

static void		set_shelf_type(t_doom *doom, uint8_t *type)
{
	t_ray		ray;

	ray = init_ray(doom, doom->own_event.hold_x);
	*type = find_shelf(doom->lib, ray, doom->i_sector, doom->i_sector);
}

static bool		mouse_in_range(int mouse_x, int mouse_y, SDL_Rect pos)
{
	if (mouse_x >= pos.x && mouse_x <= (pos.x + pos.w + 12) &&
		mouse_y >= pos.y && mouse_y <= (pos.y + pos.h + 12))
		return (true);
	else
		return (false);
}

static bool			click_on_basket(t_list **basket, uint8_t *type, int x, int y)
{
	t_list		*temp;
	t_item		*item;

	temp = *basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		if (mouse_in_range(x, y, item->position))
		{
			*type = item->type;
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

void			handle_groceries(t_doom *doom)
{
	uint8_t		type;
	int			x;
	int			y;

	SDL_GetMouseState(&x, &y);
	if (!doom->groceries->shopping_list || !doom->groceries->shopping_list_len)
		return ;
	if (click_on_basket(&doom->groceries->basket, &type, x, y))
	{
		remove_item_from_basket(&doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
	if (doom->own_event.select)
	{
		set_shelf_type(doom, &type);
		add_item_to_basket(doom, &doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
}
