#ifndef GAMEPLAY_H
# define GAMEPLAY_H

#include <stdlib.h>
#include "../libft/libft.h"

void	handle_groceries();
void	add_item_to_basket(t_list **head, uint8_t type);
bool	remove_item_from_basket(t_list **head, uint8_t item);
bool	search_basket(t_item *item, t_list **head);
uint8_t get_basket_len(t_list **head);
bool	is_in_basket(t_item *item, uint8_t type);
bool	change_amount(t_item *item, int8_t amount);
void	draw_basket_ui(t_groceries *groceries);
void	draw_shopping_ui(t_groceries *groceries);
void	del_node(t_list **head, t_list *node);
void	print_basket(t_list **basket);

#endif
