/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 22:56:12 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_EDITOR_H
# define GAME_EDITOR_H

# include "doom.h"

typedef struct s_doom		t_doom;
typedef struct s_ray		t_ray;
typedef struct s_line		t_line;
typedef struct s_point		t_point;
typedef struct s_sector		t_sector;
typedef struct s_sidedef	t_sidedef;
typedef struct s_sprite		t_sprite;
typedef struct s_lib		t_lib;
typedef struct s_item		t_item;

# define LEVEL_SPRITE_LEN 5

# define FRAME_COUNT 8
# define FRAME_WIDTH 32
# define FRAME_HEIGHT 32
# define SIDEBAR_SECTOR 160
# define SIDEBAR_SIDEDEF 640
# define MINUS_X 160
# define MINUS_Y 0
# define PLUS_X 672
# define PLUS_Y 0
# define AR_LEFT_M_X 160
# define AR_LEFT_M_Y 300
# define AR_RIGHT_M_X 608
# define AR_RIGHT_M_Y 300
# define AR_UP_M_X 400
# define AR_UP_M_Y 568
# define AR_DOWN_M_X 400
# define AR_DOWN_M_Y 0

# define AR_LEFT_X 0
# define AR_LEFT_Y 490
# define AR_RIGHT_X 128
# define TEX_SPR_X 50
# define TEX_SPR_Y 470

# define AR_LEFT_S_X 669
# define AR_LEFT_S_Y 150
# define AR_RIGHT_S_X 739
# define AR_RIGHT_S_Y 150

# define CROSS_P_X 704
# define CROSS_P_Y 500
# define CROSS_SC_X 65
# define CROSS_SC_Y 380

# define PLUS_P_X 704
# define PLUS_P_Y 330

# define RM_SD_X 704
# define RM_SD_Y 320
# define RM_SC_Y 420

# define DEL_OBJ_X 714
# define DEL_OBJ_Y 225

# define AR_LEFT_TS2_X 640
# define AR_LEFT_TS2_Y 240
# define TEX_S2_X 696
# define TEX_S2_Y 230
# define AR_RIGHT_TS2_X 768
# define AR_RIGHT_TS2_Y 240

# define HF_MAX 20
# define HF_MIN -20
# define HF_DIFF 40
# define HF_X 0
# define HF_Y 150
# define HF_HEIGHT 5
# define HF_LEN 160.0

# define HC_MAX 20
# define HC_MIN -20
# define HC_DIFF 40
# define HC_X 0
# define HC_Y 225
# define HC_HEIGHT 5
# define HC_LEN 160.0

# define LL_MAX 20
# define LL_MIN 0
# define LL_DIFF 20
# define LL_X 0
# define LL_Y 300
# define LL_HEIGHT 5
# define LL_LEN 160.0

# define SHOPPER 9
# define FACE_MASK 13
# define HEALTH_PACK_PLUS 14
# define HEALTH_PACK 15
# define CORONA 19
# define SPR_CHECKOUT 112

# define SMALL 16
# define MEDIUM 32
# define LARGE 48
# define X_LARGE 64

# define BLOCK 1
# define NO_BLOCK 0

# define START_X_S

# define LENGTH_SMALL 5
# define LENGTH_LARGE 10

static const t_line sc_lines[] = {
	{{165, 5}, {261, 101}},
	{{261, 5}, {453, 293}},
	{{453, 101}, {613, 197}},
	{{453, 197}, {635, 453}},
	{{453, 453}, {571, 549}},
	{{389, 389}, {453, 453}},
	{{325, 293}, {389, 453}},
	{{165, 293}, {325, 549}},
	{{165, 101}, {261, 293}},
	{{165, 549}, {389, 595}},
	{{389, 453}, {453, 595}}
};

static const int ed_sprites[] = {
	SHOPPER,
	CORONA,
	FACE_MASK,
	HEALTH_PACK_PLUS,
	HEALTH_PACK,
	CORONA,
	SPR_CHECKOUT,
};

static const int ed_textures[] = {
	14,
	17,
	15,
	16,
	19,
	23,
	27,
	28,
	34,
	39,
	62,
	64,
	74,
	75,
};

typedef enum		e_game_editor_im
{
	plus,
	arrow_left,
	arrow_right,
	arrow_up,
	arrow_down,
	garbage,
	player
}					t_game_editor_im;

typedef struct			s_ed_sprite
{
	int					id;
	int					type;
	t_point				pos;
	int					sector;
	struct s_ed_sprite	*next;
	struct s_ed_sprite	*previous;
}						t_ed_sprite;

typedef struct			s_ed_sector
{
	int					id;
	int					n_sidedefs;
	int					i_sidedefs;
	int					height_floor;
	int					height_ceiling;
	int					light_level;
	struct s_ed_sector	*next;
	struct s_ed_sector	*previous;
}						t_ed_sector;

typedef struct			s_ed_sidedef
{
	int					id;
	t_line				line;
	int					texture;
	int					sector;
	int					opp_sector;
	struct s_ed_sidedef *next;
	struct s_ed_sidedef *previous;
}						t_ed_sidedef;

typedef struct			s_bar {
	int					min;
	int					max;
	int					diff;
	int					x;
	int					y;
	int					height;
	int					len;
	int					cur_height;
}						t_bar;

typedef struct			s_point_int
{
	int					x;
	int					y;
}						t_point_int;

typedef struct			s_angle_line {
	t_point_int			diff;
	t_point				steps;
	t_point				start;
}						t_angle_line;

void					open_game_editor(t_doom *doom, double dt);
void					add_sector(t_doom *doom);
bool					check_sector_in_sector(t_doom *doom, int x, int y);
void					save_current_sector(t_doom *doom, int x, int y);
t_sector				*light_correction(t_sector *sector, int len);
void					mouse_press_game_editor(t_doom *doom, int x, int y);
void					bars(Uint32 **pixels, t_doom *doom);
void					draw_images(Uint32 *pixels, t_doom *doom);
void					init_game_design(t_doom *doom);
void					draw_ed_sidedef(t_doom *doom, Uint32 **pixels, \
							t_sidedef *sidedef);
void					add_sprite(t_doom *doom, int x, int y);
void					draw_ed_sprite(t_doom *doom, Uint32 **pixels);
void					highlight_curr_sector(t_doom *doom);
void					draw_screen_colors(Uint32 *pixels, t_doom *doom);
void					add_lists_to_libs(t_doom *doom);
void					put_images(int x, int y, int index, t_doom *doom);
void					put_textures_sidedef(int x, int y, int index, \
							t_doom *doom);
void					put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
							Uint32 pixel_dex);
void					mouse_press_sidedef(t_doom *doom, int x, int y);
void					put_sprite(t_doom *doom, int x, int y);
void					delete_sprite(t_doom *doom);
void					set_sector_lib(t_doom *doom);
void					set_sprite_lib(t_doom *doom);
void					set_groceries_in_level(t_doom *doom);
void					set_spr_corona(t_sprite *sprite);
void					set_spr_health_pack(t_sprite *sprite);
void					set_spr_health_pack_pl(t_sprite *sprite);
void					set_spr_checkout(t_sprite *sprite);
void					set_spr_lines(t_sprite *sprite, int lenght);
void					set_sprite_values(t_doom *doom, t_sprite *sprite, \
							t_ed_sprite *ed_sprite, int *index);
#endif
