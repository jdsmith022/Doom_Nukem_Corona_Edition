# include "../../includes/doom.h"
# include "../../includes/gameplay.h"
# include <stdio.h>

static uint8_t		*get_groceries()
{
	// This function is unnecessary
	// since all groceries are constants and shopping lists will 
	// be embedded in the lvl file
	uint8_t	*groceries;
	uint8_t	i;

	i = 0;
	groceries = ft_memalloc(sizeof(uint8_t) * GROCERY_LENGTH);
	while (i < GROCERY_LENGTH)
	{
		groceries[i] = (i + i);
		i++;
	}
	return groceries;
}

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

void	init_groceries(t_doom *doom)
{
	doom->groceries = (t_groceries *)ft_memalloc(sizeof(t_groceries)); // NOTE: FREE
	doom->groceries->shopping_list = get_shopping_list(doom, get_groceries());
	doom->groceries->shopping_list_len = SHOPPING_LIST_LENGTH;
	doom->groceries->basket = NULL;
}

static void		set_shelf_type(t_doom *doom, uint8_t *type)
{
	t_ray	ray;

	ray = init_ray(doom, MOUSE_X);
	*type = find_shelf(doom, ray, doom->i_sector, doom->i_sector);
}

bool	mouse_in_range(int mouse_x, int mouse_y, SDL_Rect pos)
{
	if (mouse_x >= pos.x && 
		mouse_x <= pos.x + pos.w &&
		mouse_y >= pos.y &&
		mouse_y <= pos.y + pos.h)
		return true;
	else return false;
}

uint8_t		click_on_basket(t_list **basket, uint8_t *type, int x, int y)
{
	t_list *temp;
	t_item *item;

	temp = *basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		if (mouse_in_range(x, y, item->position))
			return item->type;
		temp = temp->next;
	}
	return false;
}

void	groceries(t_doom *doom)
{
	uint8_t type;

	if (MOUSE_PRESSED)
	{
		set_shelf_type(doom, &type);
		if (type)
			add_item_to_basket(doom, &doom->groceries->basket, type);
		if (click_on_basket(&doom->groceries->basket, &type, MOUSE_X, MOUSE_Y))
			remove_item_from_basket(&doom->groceries->basket, type);
		print_basket(&doom->groceries->basket);
	}
	draw_basket_ui(doom, doom->groceries);
	draw_shopping_ui(doom, doom->groceries);
}
