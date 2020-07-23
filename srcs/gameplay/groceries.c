# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

// Render basket + shopping text
// Delete item from basket frontend

bool	checkout_basket(t_groceries groceries)
{
	uint8_t i;

	i = 0;
	if (groceries.shopping_list_len != get_basket_len(&groceries.basket))
		return false;
	while (i < groceries.shopping_list_len)
	{
		if (!search_basket(&groceries.shopping_list[i], &groceries.basket))
			return false;
		i++;
	}
	return true;
}

static void		set_shelf_type(t_doom *doom, uint8_t *type)
{
	t_ray	ray;

	ray = init_ray(doom, MOUSE_X);
	*type = find_shelf(doom, ray, doom->i_sector, doom->i_sector);
}

bool	mouse_in_range(int mouse_x, int mouse_y, SDL_Rect pos)
{
	printf("moosex: %d mousey: %d\n", mouse_x, mouse_y);
	printf("posx: %d posy: %d\n", pos.x, pos.y);
	if (mouse_x >= pos.x && mouse_x <= pos.x + pos.w &&
		mouse_y >= pos.y && mouse_y <= pos.y + pos.h)
		return true;
	else 
		return false;
}

uint8_t		click_on_basket(t_list **basket, uint8_t *type, int x, int y)
{
	t_list *temp;
	t_item *item;

	temp = *basket;
	while (temp)
	{
		printf("next\n");
		item = (t_item *)temp->content;
		if (mouse_in_range(x, y, item->position))
			return item->type;
		temp = temp->next;
	}
	return false;
}

void	handle_groceries(t_doom *doom)
{
	uint8_t type;

	if (!handle_mouse_state(doom))
		return ;
	if (click_on_basket(&doom->groceries->basket, &type, MOUSE_X, MOUSE_Y)){
		printf("Remove\n");
		remove_item_from_basket(&doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
	else
	{
		set_shelf_type(doom, &type);
		add_item_to_basket(doom, &doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
}

void	groceries(t_doom *doom)
{
	if (MOUSE_PRESSED)
		handle_groceries(doom);
	else
		doom->own_event.mouse_state_switched = false;
	draw_basket_ui(doom, doom->groceries);
	draw_shopping_ui(doom, doom->groceries);
}
