#ifndef GAMEPLAY_H
# define GAMEPLAY_H

#include <stdlib.h>
#include "../libft/libft.h"

# define APPLE		1
# define ORANGE		2
# define BANANA		3
# define PINEAPPLE	4
# define CHOCOLADE	5
# define SOAP		6
# define CORONA		7
# define WINE		8

# define GROCERIES	8
# define SHOPPING_LIST 4

typedef struct	s_item {
	uint8_t		type;
	uint8_t		amount;
}				t_item;

typedef struct	s_groceries {
	t_item 		*shopping_list;
	uint8_t		shopping_list_len;
	t_list		*basket;
}				t_groceries;

void	handle_groceries();
void	add_item_to_basket(t_list **head, uint8_t type);
bool	remove_item_from_basket(t_list **head, uint8_t item);
void	print_basket(t_list **basket);

#endif
