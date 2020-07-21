#ifndef GAMEPLAY_H
# define GAMEPLAY_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../sdl/includes/SDL.h"

#define GROCERY_LENGTH 5
#define SHOPPING_LIST_LENGTH 1

typedef struct s_doom	t_doom;

typedef struct			s_item {
	uint8_t				type;
	uint8_t				amount;
	SDL_Surface			*sprite;
}						t_item;

typedef struct			s_groceries {
	t_item 				*shopping_list;
	uint8_t				shopping_list_len;
	t_list				*basket;
}						t_groceries;

void					init_groceries(t_doom *doom);
void					groceries(t_doom *doom);
void					add_item_to_basket(t_doom *doom, t_list **head, uint8_t type);
bool					remove_item_from_basket(t_list **head, uint8_t item);
bool					search_basket(t_item *item, t_list **head);
uint8_t 				get_basket_len(t_list **head);
bool					is_in_basket(t_item *item, uint8_t type);
bool					change_amount(t_item *item, int8_t amount);
void					del_node(t_list **head, t_list *node);
void					print_basket(t_list **basket);
t_item 					*get_shopping_list(uint8_t *groceries);

void					draw_basket_ui(t_doom *doom, t_groceries *groceries);
void					draw_shopping_ui(t_doom *doom);

#endif
