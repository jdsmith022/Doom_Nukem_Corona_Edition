# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

// TODO: Define all groceries
// TODO: Get list of all groceries
// TODO: Generate shopping list
// TODO: add_to_basket
// TODO: remove_from_basket

// TODO: Checkout basket function (game over / level completed)

static uint8_t		*get_groceries()
{
	uint8_t	*groceries;
	uint8_t	i;

	i = 0;
	groceries = ft_memalloc(sizeof(uint8_t) * GROCERIES);
	while (i < GROCERIES)
	{
		groceries[i] = (i + i);
		i++;
	}
	return groceries;
}

uint8_t 		*get_shopping_list(uint8_t *groceries)
{
	uint8_t *shopping_list;
	uint8_t i;

	i = 0;
	shopping_list = ft_memalloc(sizeof(uint8_t) * SHOPPING_LIST);
	while (i < SHOPPING_LIST)
	{
		shopping_list[i] = (rand() % GROCERIES - 1) + 1;
		i++;
	}
	return shopping_list;
}

void	print_shopping_list(uint8_t *shopping_list)
{
	uint8_t i;

	i = 0;
	while (i < SHOPPING_LIST)
	{
		printf("%d ", shopping_list[i]);
		i++;
	}
	printf("\n");
}

bool	checkout_basket(t_groceries groceries)
{
	return true;	
}

void	handle_groceries()
{
	t_groceries	groceries;
	uint8_t		i;

	i = 0;
	groceries.shopping_list = get_shopping_list(get_groceries());
	groceries.basket = NULL;
	print_shopping_list(groceries.shopping_list);
	add_item_to_basket(&groceries.basket, BANANA);
	add_item_to_basket(&groceries.basket, ORANGE);
	add_item_to_basket(&groceries.basket, CHOCOLADE);
	add_item_to_basket(&groceries.basket, SOAP);
	print_basket(&groceries.basket);
	remove_item_from_basket(&groceries.basket, CHOCOLADE);
	remove_item_from_basket(&groceries.basket, BANANA);
	remove_item_from_basket(&groceries.basket, ORANGE);
	remove_item_from_basket(&groceries.basket, SOAP);
	print_basket(&groceries.basket);
}
