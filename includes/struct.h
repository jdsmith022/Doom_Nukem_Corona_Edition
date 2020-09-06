#ifndef STRUCT_H
# define STRUCT_H

# include "doom.h"

# define NAME "Doom Nukem Corona Edition"

# define TRUE 1
# define FALSE 0

# define NUM_LEVELS 1

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"
# define OPEN_ERR	"error: opening file"
# define FONT_ERR	"error: writing font to screen"

# define WIDTH 800
# define HEIGHT 600

# define STD_TEXT_HEIGHT 96

# define PI 3.14159265359

# define PLAYER_HEIGHT 50
# define MOVE_SPEED 100
# define SENSITIVITY 0.4
# define GRAVITY -2
# define VELOCITY  5

# define RED 1
# define GREEN 2
# define BLUE 3
# define FONT_MASK 0X36
# define WINDOW_MASK 0XFF

# define SLOPE_COLOR 0X505052

# define OUTSIDE 1
# define EXIT_LEVEL 2
# define START_SECTOR 3
# define START_TIMER 4
# define CHECKOUT 5

# define WINDOW 6

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;
typedef struct s_menu		t_menu;
typedef struct s_hud		t_hud;
typedef struct s_ed_sidedef t_ed_sidedef;
typedef struct s_ed_sector	t_ed_sector;
typedef struct s_ed_sprite	t_ed_sprite;

typedef enum			e_settings
{
	player_1,
	player_2,
	player_3,
	left,
	right,
	refill,
	refill_station,
	light,
	light_click,
	set
}						t_settings;

# pragma pack(push, 1)

typedef struct			s_rgb {
	Uint8				r;
	Uint8				g;
	Uint8				b;
}						t_rgb;

# pragma pack(pop)

typedef struct			s_rgb_d {
	double				r;
	double				g;
	double				b;
}						t_rgb_d;

typedef struct			s_coord {
	uint16_t			x;
	uint16_t			y;
}						t_coord;

typedef struct			s_point {
	double				x;
	double				y;
}						t_point;

typedef struct			s_line {
	t_point				start;
	t_point				end;
}						t_line;

typedef struct			s_sprite {
	int					index;
	int					amount;
	t_point				pos;
	t_point				sprite_begin;
	double				size;
	t_line				*lines;
	int					action;
	int					*textures;
	int					block;
	int					sector;
	int					n_sector;
	double				width;
	double				height;
	double				sprite_x;
	double				sprite_y;
	int					visible;
	double				distance;
	int					prev_sectors[50];
}						t_sprite;

typedef struct			s_ray {
	t_line				line;
	double				angle;
	double				plane_x;
	int					filter;
}						t_ray;

typedef struct		s_event {
	bool			mouse_press;
	bool			mouse_state_switched;
	bool			jump;
	bool			bend;
	bool			select;
	bool			shoot;
	bool			mouse_pointer;
	bool			set_step;
	int				sliding_door;
	int				hold_angle;
	int				hold_x;
	int				hold_y;
	int				move_pos_f;
	int				move_pos_b;
	int				move_pos_l;
	int				move_pos_r;
	int				floor_diff;
	int				ceiling_diff;
	int				next_sector_height;
	int				step_down;
	double			velocity;
	int				y_pitch;
	int				hit_index;
	bool			virus_red;
	int				virus_red_i;
	bool			corona_hit;
	bool			scissor_lift;
	bool			scissor_lift_up;
	bool			scissor_lift_down;
	bool			parked_too_close;
	bool			fall;
	bool			mist;
	bool			spray_mist;
	bool			trolly;
	bool			light_switch;
	bool			light_switch_changed;
	bool			refill;
	bool			spray_shopper;
	bool			sprite_collision;
	bool			toilet_paper;
	bool			window;
	int				sprite_collision_dist;
	int				sprite_index;
	struct timespec	light_time;
	int				sd_action;
	double			hold_light;
	int				hold_light_sector;
	int				click_light;
	int				fall_count;
	bool			groc_pickup;
	bool			died;
	int				sanitizer_refills;
	struct timespec	refill_pause;
	struct timespec	sprite_timer;
}					t_event;

typedef struct		s_object
{
	int				n_textures;
	int*			textures;
	int*			face_ang;
	char*			name;
	int				action;
	t_line			location;
}					t_object;

typedef struct		s_plane
{
	t_point			intersect;
	t_line			line;
	int				x;
	int				sidedef_top;
	int				sidedef_bottom;
	int				sidedef_height;
	int				mid_texture_top;
	int				mid_texture_bottom;
	double			height_standard;
	int				ceiling_start;
	int				floor_start;
	int				wall_offset;
}					t_plane;

typedef struct		s_prev_sidedef {
	int				id;
	double			distance;
	t_point			intersect;
}					t_prev_sidedef;

typedef struct		s_window {
	int				index;
	int				x_start;
	int				x_end;
	int				y_pixel_top[WIDTH];
	int				y_pixel_bottom[WIDTH];
	double			height_standard[WIDTH];
	int				wall_offset[WIDTH];
	double			sidedef_offset[WIDTH];
	int				opp_sector;
	int				curr_sector;
}					t_window;

typedef struct		s_sidedef {
	t_point			intersect;
	t_line			line;
	int				id;
	int				action;
	int				sector;
	int				opp_sector;
	double			offset;
	int				dir;
	int				txt_1;
	int				txt_2;
	int				txt_3;
	double			distance;
	double			angle;
	int				poster;
	t_prev_sidedef	prev_sidedef;
}					t_sidedef;

typedef struct		s_sector {
	int				id;
	int				action;
	int				n_sidedefs;
	int				i_sidedefs;
	int				n_objects;
	int				i_objects;
	double			light_level;
	double			hold_light;
	int				light;
	int				slope_floor_id;
	int				slope_ceiling_id;
	double			slope_ceiling;
	double			slope_floor;
	int				floor_end;
	int				ceiling_end;
	double			height_ceiling;
	double			height_floor;
	int				txt_ceiling;
	int				txt_floor;
	int				diff_x;
	int				diff_y;
	// int				bottom[WIDTH];
	// int				top[WIDTH];
	// int				mid_bottom[WIDTH];
	// int				mid_top[WIDTH];
}					t_sector;

typedef struct		s_lib {
	SDL_Surface		**tex_lib;
	int				len_tex_lib;
	SDL_Surface		**obj_lib;
	int				len_obj_lib;
	SDL_Surface		**sky_lib;
	t_line			*sky_sd;
	SDL_Surface		**player_lib;
	int				len_player_lib;
	t_font_lib		font_lib;
	int				portal_ceiling;
	int				len_sky_lib;
	t_sector		*sector;
	int				n_sectors;
	t_sidedef		*sidedef;
	int				len_sidedef;
	t_sidedef		*infection;
	int				cur_len_infection;
	int				tot_len_infection;
	t_sprite		*sprites;
	t_window		window;
	int				*sprite_order;
	double			light;
	int				sprite_height[20];
	int				move;
}					t_lib;

typedef struct		s_gamedesign {
	bool			edit_sector;
	bool			place_checkout;
	bool			open_connection;
	bool			custom_level;
	bool			pl_pos;
	t_ed_sector		*ed_sector;
	t_ed_sector		*sc_head;
	t_ed_sidedef	*ed_sidedef;
	t_ed_sidedef	*sd_head;
	t_ed_sprite		*ed_sprite;
	t_ed_sprite		*sp_head;
	int				cur_sector;
	int				sd_tex_index[12];
	int				ed_spr_index[7];
	int				cur_sprite;
	int				spr_tex;
	int				sd_len;
	int				sc_len;
	int				spr_len;
	int				n_sprites;
	int				i_sprites;
	int				tex_index;
	double			floor_height;
	double			ceiling_height;
	double			light_level;
	t_line			draw_line;
	t_point			start_sector;

	int				s_size;
	int				w_len;
	int				w_size;
	t_sprite		*object;
	int				object_bar;
	int				sidedef_bar;
	SDL_Surface		**sym_lib;
}					t_gamedesign;

typedef struct		s_player
{
	int				spray_hand;
	int				spraying_hand;
	int				left_select;
	int				right_select;
	int				character;
	int				handed;
	double			std_height;
	double			height;
}					t_player;

typedef struct		s_game_state
{
	bool			is_running;
	bool			editor;
	bool			light;
	bool			hud_display;
	bool			start_timer;
	struct timespec	start_time;
	int				difficulty;
	int				play_time;
	int				save_poster;

}					t_game_state;

typedef struct		s_ray_casting
{
	int				texture_width;
	int				texture_height;
	int				poster;
	double			dir_angle;
	double			ray_angle;
	double			ray_adjacent;
	double			max_ray;
	double			distance;
	double			horizontal_plane_dist;
	double			dist_to_plane;
}					t_ray_casting;

typedef struct		s_render
{
	t_sidedef		near_sidedef;
	t_point			intersect;
	double			distance;
	double			min_distance;
}					t_render;

typedef struct		s_doom {
	t_line			tests;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Event		event;
	SDL_Cursor		*cursor;
	t_lib			lib;
	t_point			pos;
	t_event			own_event;
	t_gamedesign	game_design;
	t_audio			*audio;
	t_groceries		*groceries;
	t_menu			*menu;
	t_hud			*hud;
	t_player		player;
	t_game_state	game;
	t_ray_casting	cast;
	t_prev_sidedef	prev_sidedef;
	int				i_sidedef;
	int				i_sector;
	int				prev_sector;
	int				obj_height;
	int				visible_sprites;
	int				total_sprites;
	double			stripe_distance[WIDTH];
	int				save_scissor_lift;
}					t_doom;

#endif