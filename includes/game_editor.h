#ifndef GAME_EDITOR_H
# define GAME_EDITOR_H

// # include <stdint.h>

#include "doom.h"

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

# define DEL_SECTOR_X 65
# define DEL_SECTOR_Y 550

# define AR_LEFT_X 0
# define AR_LEFT_Y 400
# define AR_RIGHT_X 128
# define TEX_SPR_X 50
# define TEX_SPR_Y 380

# define AR_LEFT_S_X 664
# define AR_LEFT_S_Y 160
# define AR_RIGHT_S_X 744
# define AR_RIGHT_S_Y 160

# define CROSS_P_X 714
# define CROSS_P_Y 500

# define PORTAL_X 714
# define PORTAL_Y 240
# define RM_SD_X 714
# define RM_SD_Y 320
# define RM_SC_Y 420

# define DEL_OBJ_X 714
# define DEL_OBJ_Y 225

# define AR_LEFT_SC_X 664
# define AR_LEFT_SC_Y 300
# define AR_RIGHT_SC_X 744
# define AR_RIGHT_SC_Y 300

# define AR_LEFT_TF_X 0
# define AR_LEFT_TF_Y 375
# define TEX_FL_X 56
# define TEX_FL_Y 375
# define AR_RIGHT_TF_X 128
# define AR_RIGHT_TF_Y 375

# define AR_LEFT_TC_X 0
# define AR_LEFT_TC_Y 450
# define TEX_CE_X 56
# define TEX_CE_Y 450
# define AR_RIGHT_TC_X 128
# define AR_RIGHT_TC_Y 450

# define AR_LEFT_TS1_X 640
# define AR_LEFT_TS1_Y 375
# define TEX_S1_X 696
# define TEX_S1_Y 375
# define AR_RIGHT_TS1_X 768
# define AR_RIGHT_TS1_Y 375

# define AR_LEFT_TS2_X 640
# define AR_LEFT_TS2_Y 80
# define TEX_S2_X 696
# define TEX_S2_Y 80
# define AR_RIGHT_TS2_X 768
# define AR_RIGHT_TS2_Y 80

# define AR_LEFT_TS3_X 640
# define AR_LEFT_TS3_Y 525
# define TEX_S3_X  696
# define TEX_S3_Y 525
# define AR_RIGHT_TS3_X 768
# define AR_RIGHT_TS3_Y 525

# define SIDEDEF_BUTTON_X 640
# define SIDEDEF_BUTTON_Y 568

# define SECTOR_BUTTON_X 768
# define SECTOR_BUTTON_Y 568

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

# define SCISSOR_LIFT 7
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

/*game editor*/
void					open_game_editor(t_doom *doom, double dt);
void					set_ed_sidedef_values(t_doom *doom, t_line line);
void					check_connection(t_doom *doom, int x, int y);
void					add_sidedef(t_doom *doom, int x, int y);
bool					snap_close_sector(t_doom *doom, t_point start, \
							t_point *end);
void					delete_sector(t_doom *doom);
void					add_sector(t_doom *doom);
void					set_ed_sector_values(t_doom *doom);
t_line					set_ray(t_doom *doom, t_line ray);
bool					check_sector_in_sector(t_doom *doom, t_line ray);
void					save_current_sector(t_doom *doom, t_line ray);
t_sector				*light_correction(t_sector *sector, int len);
void					mouse_press_game_editor(t_doom *doom, int x, int y);
void					bars(Uint32 **pixels, t_doom *doom);
void					draw_images(Uint32 *pixels, t_doom *doom);
void					init_game_design(t_doom *doom);
void					draw_ed_sidedef(t_doom *doom, Uint32 **pixels, \
							t_ed_sidedef *ed_sidedef);
void					add_sprite(t_doom *doom, int x, int y);
void					draw_ed_sprite(t_doom *doom, Uint32 **pixels);
void					draw_screen_colors(Uint32 *pixels, t_doom *doom);
void					add_lists_to_libs(t_doom *doom);
void					put_images(int x, int y, int index, t_doom *doom);
void					put_textures_sidedef(int x, int y, int index, \
							t_doom *doom);
void					put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
							Uint32 pixel_dex);
void					mouse_press_sidedef_txt(t_doom *doom, int x, int y);
void					mouse_press_sidedef(t_doom *doom, int x, int y);
void					put_sprite(t_doom *doom, int x, int y);
bool					line_intersect(t_doom *doom, t_point start, int x, \
							int y);
void					delete_sidedef(t_doom *doom);
void					delete_sprite(t_doom *doom);
void					delete_sprites_in_sector(t_doom *doom, int sector);
void					set_sector_lib(t_doom *doom);
void					set_sidedef_lib(t_doom *doom);
void					set_sprite_lib(t_doom *doom);
void					set_groceries_in_level(t_doom *doom, t_item *t_types);
void					set_spr_corona(t_sprite *sprite);
void					set_spr_health_pack(t_sprite *sprite);
void					set_spr_health_pack_pl(t_sprite *sprite);
void					set_spr_checkout(t_sprite *sprite);
void					set_spr_lines(t_sprite *sprite, int lenght);
void					set_sprite_values(t_doom *doom, t_sprite *sprite, \
							t_ed_sprite *ed_sprite, int *index);
void					create_mid_points(t_line *line, int diff);
void					place_checkout(t_doom *doom);
void					check_placement(t_doom *doom, t_ed_sidedef *sidedef,
							t_line line);
#endif
