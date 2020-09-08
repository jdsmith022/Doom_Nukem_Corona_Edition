/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:10:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:36:17 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../sdl/includes/SDL.h"
# include "font.h"

typedef struct s_doom	t_doom;
typedef struct s_ray	t_ray;
typedef struct s_coord	t_coord;
typedef struct s_lib	t_lib;
typedef struct s_sprite	t_sprite;

# define MAX_SL_LEN		4
# define MAX_BASKET_LEN 8

typedef struct			s_item {
	uint8_t				type;
	uint8_t				amount;
	SDL_Surface			*sprite;
	SDL_Rect			position;
}						t_item;

typedef struct			s_game_over {
	bool				won;
	t_item				*groceries_to_display;
	uint8_t				groceries_len;
}						t_game_over;

typedef struct			s_groceries {
	uint8_t				num_of_groceries;
	t_item				*groceries_in_level;
	t_item				*shopping_list;
	uint8_t				shopping_list_len;
	uint8_t				basket_len;
	t_list				*basket;
	TTF_Font			*font;
	t_game_over			info;
}						t_groceries;

void					init_groceries(t_doom *doom);
void					groceries(t_doom *doom);
void					handle_groceries(t_doom *doom);
void					add_item_to_basket(t_doom *doom, t_list **head, \
											uint8_t type);
bool					remove_item_from_basket(t_list **head, uint8_t item);
bool					is_in_basket(t_item *item, uint8_t type);
bool					change_amount(t_item *item, int8_t amount);
void					del_node(t_list **head, t_list *node);
void					del_groceries(t_groceries *groc);
void					print_basket(t_list **basket);
void					generate_shopping_list(t_doom *doom);
void					custom_shopping_list(t_doom *doom,
											t_groceries *groceries);
bool					checkout(t_groceries *groceries);
void					draw_basket_ui(t_doom *doom, t_groceries *groceries);
void					draw_shopping_ui(t_doom *doom, t_groceries *groceries);
void					set_positions(t_list **basket);
void					draw_grocery_amount(t_doom *doom, SDL_Rect rect, \
									char *text);
void					draw_text_at(t_doom *doom, SDL_Rect rect, char *text);
t_ray					init_ray(t_doom *doom, int x);
int						find_shelf(t_lib lib, t_ray ray, int sector, \
									int prev_sector);
uint8_t					get_basket_len(t_list **head);
t_item					*get_item_from_basket(uint8_t type, t_list **head);
SDL_Rect				get_position(uint16_t index, int start_x, int start_y);
void					set_positions(t_list **basket);
bool					search_basket(t_item *itema, t_list **head);
bool					search_basket_for_item(t_item *itema, t_list **head);
void					get_game_over_info(t_doom *doom);
void					timer(t_doom *doom);
/*
**						Shooting
*/

void					check_sprite_hit(t_doom *doom);
void					check_select_spray_sprite(t_doom *doom);
int						sprite_in_range(t_doom *doom, t_ray ray, int sprite_i,
						int prev_sector);

#endif
