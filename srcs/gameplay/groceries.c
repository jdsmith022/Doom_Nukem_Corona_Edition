# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

static uint8_t		*get_groceries()
{
	// This function is unnecessary
	// since all groceries are constants and shopping lists will 
	// be embedded in the lvl file
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

t_item 		*get_shopping_list(uint8_t *groceries)
{
	t_item *shopping_list;
	uint8_t i;

	i = 0;
	shopping_list = ft_memalloc(sizeof(t_item) * SHOPPING_LIST);
	while (i < SHOPPING_LIST)
	{
		shopping_list[i].type = (rand() % GROCERIES) + 1;
		shopping_list[i].amount = (rand() % 5) + 1;
		i++;
	}
	return shopping_list;
}

void	print_shopping_list(t_item *shopping_list)
{
	uint8_t i;

	i = 0;
	while (i < SHOPPING_LIST){
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

void	handle_groceries()
{
	t_groceries	groceries;
	uint8_t		i;

	i = 0;
	groceries.shopping_list = get_shopping_list(get_groceries());
	groceries.shopping_list_len = SHOPPING_LIST;
	groceries.basket = NULL;
	print_shopping_list(groceries.shopping_list);
	add_item_to_basket(&groceries.basket, 8);
	add_item_to_basket(&groceries.basket, 8);
	add_item_to_basket(&groceries.basket, 8);
	add_item_to_basket(&groceries.basket, 8);
	add_item_to_basket(&groceries.basket, 8);
	add_item_to_basket(&groceries.basket, 2);
	add_item_to_basket(&groceries.basket, 2);
	add_item_to_basket(&groceries.basket, 2);
	add_item_to_basket(&groceries.basket, 2);
	add_item_to_basket(&groceries.basket, 3);
	add_item_to_basket(&groceries.basket, 3);
	add_item_to_basket(&groceries.basket, 3);
	add_item_to_basket(&groceries.basket, 1);
	add_item_to_basket(&groceries.basket, 1);
	add_item_to_basket(&groceries.basket, 1);
	print_basket(&groceries.basket);
	printf("%d\n" , checkout_basket(groceries));
}
