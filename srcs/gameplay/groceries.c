# include "../../includes/doom.h"

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

t_item 		*get_shopping_list(uint8_t *groceries)
{
	t_item *shopping_list;
	uint8_t i;

	i = 0;
	shopping_list = ft_memalloc(sizeof(t_item) * SHOPPING_LIST_LENGTH);
	while (i < SHOPPING_LIST_LENGTH)
	{
		shopping_list[i].type = (rand() % GROCERY_LENGTH) + 1;
		shopping_list[i].amount = (rand() % 5) + 1;
		i++;
	}
	return shopping_list;
}

void	print_shopping_list(t_item *shopping_list)
{
	uint8_t i;

	i = 0;
	while (i < SHOPPING_LIST_LENGTH){
		printf("type: %d  amount: %d  ", shopping_list[i].type, shopping_list[i].amount);
		i++;
	}
	printf("\n");
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
	doom->groceries.shopping_list = get_shopping_list(get_groceries());
	doom->groceries.shopping_list_len = SHOPPING_LIST_LENGTH;
	doom->groceries.basket = NULL;
	add_item_to_basket(doom, &doom->groceries.basket, 9);
	add_item_to_basket(doom, &doom->groceries.basket, 10);
	add_item_to_basket(doom, &doom->groceries.basket, 11);
}

void	groceries(t_doom *doom)
{
	draw_basket_ui(doom, doom->groceries);
	// draw_shopping_ui(doom);
}
