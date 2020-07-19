#ifndef GAMEPLAY_H
# define GAMEPLAY_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../sdl/includes/SDL.h"

typedef struct		s_item {
	uint8_t			type;
	uint8_t			amount;
	SDL_Surface		*sprite;
}					t_item;

typedef struct		s_groceries {
	t_item 			*shopping_list;
	uint8_t			shopping_list_len;
	t_list			*basket;
}					t_groceries;

#endif
