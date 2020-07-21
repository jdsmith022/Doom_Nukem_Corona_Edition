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
# define SHOPPING_LIST 1

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
bool	search_basket(t_item *item, t_list **head);
uint8_t get_basket_len(t_list **head);
bool	is_in_basket(t_item *item, uint8_t type);
bool	change_amount(t_item *item, int8_t amount);
void	del_node(t_list **head, t_list *node);
void	print_basket(t_list **basket);

#endif
