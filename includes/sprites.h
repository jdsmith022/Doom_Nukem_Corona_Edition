/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:45:15 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "doom.h"

typedef struct s_line	t_line;
typedef struct s_sprite	t_sprite;

/*
**	sprite_functions
*/

void				sprite_init(t_doom *doom);
void				sprite_check(t_doom *doom, t_ray ray, int sector,\
					int prev_sector);
void				sprite_render(t_doom *doom);
int					*sort_sprite_array(t_sprite *sprite, int visible_sprites,\
					int total_sprites);
void				sort_sprites_window(int *sprite_order, int curr_sector,\
					int visible_sprites, t_sprite *sprite);
void				find_position(t_doom *doom, t_point *sprite_begin,\
					t_point *sprite_end, int index);
void				draw_stripes(t_doom *doom, t_line *sprite, int index_sp);
void				sprite_reset(t_doom *doom);
void				scale_sprite(t_doom *doom, t_line *coords,\
					t_sprite *sprite);
t_point				sidedef_sprite_intersect(t_line sidedef, t_line sprite);
void				find_sidedef_intersect_per_sector(t_doom *doom,\
					t_sprite *sprite, int curr_sector, int prev_sector);
int					sprite_collision(t_doom *doom, t_line movement);
void				exit_scissor_lift(t_doom *doom);
void				put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index,\
					int i);
void				remove_red_virus(t_doom *doom);
void				set_player_sprite(t_doom *doom);
void				draw_player_adds(t_doom *doom);
void				draw_stripes_bar(t_doom *doom, t_line bar, int sprite_i);
void				scale_bar(t_doom *doom, t_line *bar, int sprite_i);
int					pixel_is_white(t_doom *doom, int index);
int					virus_move(int bottom, int height, int move_value,\
					int sprite_index);
int					no_clipping_region(int screen_y, t_sprite sprite,\
					t_doom *doom, int x);
int					check_y_side_line(t_line line, int x, int y);
int					clip_top(t_doom *doom, int index_sp, int x, int screen_y);
void				sprite_light(t_doom *doom, t_sprite sprite, int y);
void				check_sprite_distance(t_doom *doom, int index);

#endif
