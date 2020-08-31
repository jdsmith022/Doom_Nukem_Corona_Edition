#ifndef GAME_EDITOR_H
# define GAME_EDITOR_H

// # include <stdint.h>

#include "doom.h"

typedef struct s_doom		t_doom;
typedef struct s_line		t_line;
typedef struct s_sector		t_sector;
typedef struct s_plane		t_plane;
typedef struct s_sidedef	t_sidedef;
typedef struct s_sprite		t_sprite;
typedef struct s_lib		t_lib;
typedef struct s_point		t_point;
typedef struct s_ray		t_ray;
typedef struct s_point		t_point;
typedef struct s_line		t_line;

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

# define DEL_SECTOR_X 104
# define DEL_SECTOR_Y 75
# define ADD_SECTOR_X 24
# define ADD_SECTOR_Y 75

# define AR_LEFT_X 24
# define AR_LEFT_Y 0
# define AR_RIGHT_X 104
# define AR_RIGHT_Y 0

# define AR_LEFT_S_X 664
# define AR_LEFT_S_Y 0
# define AR_RIGHT_S_X 744
# define AR_RIGHT_S_Y 0

# define CROSS_P_X 714
# define CROSS_P_Y 150

# define PORTAL_X 744
# define PORTAL_Y 225
# define RM_SD_X 669
# define RM_SD_Y 225

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
# define AR_LEFT_TS2_Y 450
# define TEX_S2_X 696
# define TEX_S2_Y 450
# define AR_RIGHT_TS2_X 768
# define AR_RIGHT_TS2_Y 450

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

# define HF_MAX 30
# define HF_MIN -30
# define HF_DIFF 60
# define HF_X 0
# define HF_Y 150
# define HF_HEIGHT 5
# define HF_LEN 160.0

# define HC_MAX 30
# define HC_MIN -30
# define HC_DIFF 60
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

typedef struct	s_bar {
	int			min;
	int			max;
	int			diff;
	int			x;
	int			y;
	int			height;
	int			len;
	int			cur_height;
}				t_bar;

//remove cause in a different file but couldn't find yet

typedef struct	s_poin {
	double		x;
	double		y;
}				t_poin;

typedef struct	s_point_int {
	int			x;
	int			y;
}				t_point_int;

typedef struct	s_angle_line {
	t_point_int	diff;
	t_poin		steps;
	t_poin		start;
}				t_angle_line;

/*game editor*/
void				open_game_editor(t_doom *doom);
void				add_sidedef(t_doom *doom, int x, int y);
void				del_sidedef(t_doom *doom);
void				mv_sidedef(t_sidedef **sidedef, int w_len, int id);
t_sidedef			*cpy_sidedef(t_doom *doom, t_sidedef *sidedef, int *w_size);
void				rmove(t_sprite *sprite, t_doom *doom);
t_sector			*light_correction(t_sector *sector, int len);
void				add_sector(t_doom *doom);
void				del_sector(t_gamedesign *game_design);
void				add_portal(t_doom *doom, int dir);
void				add_to_game(t_doom *doom);
void				mouse_press_game_editor(t_doom *doom, int x, int y);
void				printing_map(t_gamedesign *design);
void				bars(Uint32 **pixels, t_doom *doom);
void				draw_sector_images(Uint32 *pixels, t_doom *doom);
void				draw_images(Uint32 *pixels, t_doom *doom);
void				draw_screen_colors(Uint32 *pixels, t_doom *doom);
void				box_in_sectors(t_doom *doom);
void				init_game_design(t_doom *doom);
void				init_game_design(t_doom *doom);
void				draw_lines(t_doom *doom, Uint32 **pixels, int b);
void				add_object(t_doom *doom, int x, int y);
void				set_angle(t_angle_line *angle, double *i);
void				set_pixels(Uint32 **pixels, t_angle_line angle, int color);
void				draw_object(t_doom *doom, Uint32 **pixels);
void				draw_lines(t_doom *doom, Uint32 **pixels, int b);
void				del_obj(t_doom *doom);
void				correct_i_object(int i, t_doom *doom);
void				add_specifications(t_gamedesign *gd, int index);
void				add_obj_lines(int x, int y, t_gamedesign gd, t_line **ln);
void				coor_pos(t_doom *doom);
void				add_player(t_doom *doom, int x, int y);
void				change_sector(t_doom *doom, int change);
void				change_texture(t_doom *doom, int *texture, int change);
void				change_sidedef(t_doom *doom, int change);
void				object_change(t_doom *doom, int change);
void				sidedef_object(t_doom *doom);
void				object_texture(t_doom *doom, int change);
void				mouse_press_sidedef(t_doom *doom, int x, int y);
void				put_images(int x, int y, int index, t_doom *doom);
void				put_textures(int x, int y, int index, t_doom *doom);
void				put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex);
void				draw_screen_colors(Uint32 *pixels, t_doom *doom);

#endif