#ifndef SPRITES_H
# define SPRITES_H

#include <stdlib.h>
#include "doom.h"

# define SCISSOR_LIFT 7
# define SHOPPER 9
# define FACE_MASK 13
# define HEALTH_PACK_PLUS 14
# define HEALTH_PACK 15
# define CORONA 19

# define SMALL 16
# define MEDIUM 32
# define LARGE 48
# define X_LARGE 64

# define BLOCK 1
# define NO_BLOCK 0

# define START_X_S

# define START_X_SM -5
# define START_Y_SM -5
# define END_X_SM 5
# define END_Y_SM 5

# define START_X_L -10
# define START_Y_L -10
# define END_X_L 10
# define END_Y_L 10

# define NUM_OF_SPRITES 6

typedef struct s_line	t_line;
typedef struct s_sprite	t_sprite;

typedef struct	s_level_sprite
{
	int			index;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;
	int			tex1;
	int			tex2;
	int			tex3;
	int			tex4;
	int			block;
	int			size;
	int			action;
}				t_level_sprite;

static const	t_level_sprite level_sprites[] = {
	{SCISSOR_LIFT, START_X_L, START_Y_L, END_X_L, END_Y_L,\
		7, 8, 7, 8, BLOCK, X_LARGE, 7},
	{SHOPPER, START_X_SM, START_Y_SM, END_X_SM, END_Y_SM,\
		9, 10, 11, 12, BLOCK, LARGE, 9},
	{FACE_MASK, START_X_SM, START_Y_SM, END_X_SM, END_Y_SM,\
		13, 13, 13, 13, NO_BLOCK, SMALL, 3},
	{HEALTH_PACK_PLUS, START_X_SM, START_Y_SM, END_X_SM, END_Y_SM,\
		14, 14, 14, 14, NO_BLOCK, SMALL, 1},
	{HEALTH_PACK, START_X_SM, START_Y_SM, END_X_SM, END_Y_SM,\
		15, 15, 15, 15, NO_BLOCK, SMALL, 2},
	{CORONA, START_X_SM, START_Y_SM, END_X_SM, END_Y_SM,\
		19, 19, 19, 19, NO_BLOCK, SMALL, 4},
};

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
void				draw_stripes(t_doom *doom, t_point *sprite_begin,\
					t_point *sprite_end, int index_sp);
void				sprite_reset(t_doom *doom);
void				scale_sprite(t_doom *doom, t_point *sprite_begin,\
					t_point *sprite_end, t_sprite *sprite);
t_point				sidedef_sprite_intersect(t_line sidedef, t_line sprite);
int					sprite_collision(t_doom *doom, t_line movement);
void				exit_scissor_lift(t_doom *doom);
void				put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index,\
					int i, double distance);
void				remove_red_virus(t_doom *doom);
void				draw_player_adds(t_doom *doom);
void				draw_stripes_bar(t_doom *doom, t_line bar, int sprite_i);
void				scale_bar(t_doom *doom, t_line *bar, int sprite_i);

#endif