// #ifndef STRUCT_H
// # define STRUCT_H

// # include "doom.h"

// # define WIDTH 800
// # define HEIGHT 600

// typedef struct s_audio		t_audio;
// typedef struct s_groceries	t_groceries;
// typedef struct s_menu		t_menu;
// typedef struct s_hud		t_hud;

// # pragma pack(push, 1)

// typedef struct			s_rgb {
// 	char				r;
// 	char				g;
// 	char				b;
// }						t_rgb;

// # pragma pack(pop)

// typedef struct			s_rgb_d {
// 	double				r;
// 	double				g;
// 	double				b;
// }						t_rgb_d;

// typedef struct			s_coord {
// 	uint16_t			x;
// 	uint16_t			y;
// }						t_coord;

// typedef struct			s_point {
// 	double				x;
// 	double				y;
// }						t_point;

// typedef struct			s_line {
// 	t_point				start;
// 	t_point				end;
// }						t_line;

// typedef struct			s_sprite {
// 	int					index;			//start index
// 	int					amount;			//which side is viewed how many textures does the sprite have?
// 	t_point				pos;
// 	t_point				sprite_begin;
// 	double				size;			//products: 16, shopper: 48
// 	t_line				*lines;
// 	// double				angle;			//GEBRUIK IK NIET what is the angle on the map
// 	int					action;	//1 health green, 2 health red, 3 facemask, 4 virus green + placement, 5 virus red + placement, 6 inactive virus 7 scissor lift, 8 inactive health sprite 9 shopper
// 	int					*textures;		//index to texture, +0, +1, +2 or +3
// 	int					block;			//can the player walk through it or not
// 	int					sector;
// 	int					n_sector; //amount of checked sector stored in prev_sectors
// 	double				width;
// 	double				height;
// 	double				sprite_x;		//x cord translated to viewer space
// 	double				sprite_y;		//y cord translated to viewer space
// 	int					visible;		//this is only turned on for the drawing... can't use it for other options
// 	double				distance;
// 	// int					face;
// 	int					prev_sectors[50];	//where to empty them again? don't forget to protect
// }						t_sprite;

// typedef struct		s_ray {
// 	t_line			line;
// 	double			angle;
// 	double			plane_x;
// 	int				filter;
// }					t_ray;

// typedef struct		s_event {
// 	bool			mouse_press;
// 	bool			mouse_state_switched;
// 	bool			jump;
// 	bool			bend;
// 	bool			select;
// 	bool			shoot;
// 	int				hold_angle;
// 	int				hold_x;
// 	int				hold_y;
// 	int				cam_move_f;
// 	int				cam_move_b;
// 	int				cam_move_l;
// 	int				cam_move_r;
// 	int				floor_diff;
// 	int				ceiling_diff;
// 	int				next_sector_height;
// 	int				step_down;
// 	double			velocity;
// 	int				y_pitch;
// 	int				virus_hit_index;
// 	bool			virus_red;
// 	int				virus_red_i;
// 	bool			scissor_lift;
// 	bool			scissor_lift_up;
// 	bool			scissor_lift_down;
// 	bool			parked_too_close;
// 	bool			fall;
// 	bool			mist;
// 	bool			spray_mist;
// 	bool			trolly;
// 	bool			light_switch;
// 	bool			light_timer;
// 	struct timespec	light_time;
// 	double			hold_light;

// 	int				fall_count;
// }					t_event;

// typedef struct		s_m_object{
// 	int				amount;
// 	int*			textures;
// 	int*			face_ang;
// 	char*			name;
// 	int				action;
// 	t_line*			movement;
// 	// t_line			height;
// 	int				speed;
// 	int				spawn_time;
// }					t_m_object;

// typedef struct		s_object{
// 	int				n_textures;
// 	int*			textures;
// 	int*			face_ang;
// 	char*			name;
// 	int				action;
// 	t_line			location;
// }					t_object;

// typedef struct		s_plane
// {
// 	t_point			intersect;
// 	t_line			line;
// 	int				sidedef_top;
// 	int				sidedef_bottom;
// 	int				sidedef_height;
// 	int				mid_texture_top;
// 	int				mid_texture_bottom;
// 	double			height_standard;
// 	int				ceiling_start;
// 	int				floor_start;
// 	int				wall_offset;
// }					t_plane;

// typedef struct		s_prev_sidedef {
// 	int				id;
// 	double			distance;
// 	t_point			intersect;
// }					t_prev_sidedef;

// typedef struct		s_sidedef {
// 	t_point			intersect;
// 	t_line			line;
// 	int				id;
// 	int				action;
// 	int				sector;
// 	int				opp_sidedef;
// 	int				opp_sector;
// 	double			offset;
// 	int				dir;
// 	int				txt_1;
// 	int				txt_2;
// 	int				txt_3;
// 	double			distance;
// 	int				infection;
// 	int				poster;
// 	t_prev_sidedef	prev_sidedef;
// }					t_sidedef;

// typedef	struct		s_slope {
// 	double			distance;
// 	double			height;
// 	double			bottom_height;
// 	int				bottom_plane;
// 	double			dist_to_bottom;
// 	int				opp_side;
// 	int				sidedef_id;
// 	int				prev_floor_id;
// 	int				prev_ceiling_id;
// 	double			delta_height;
// 	t_point			intersect;
// 	t_point			prev_intersect;
// 	t_point			conn_point;
// }					t_slope;

// typedef struct		s_sector {
// 	int				id;
// 	int				action;
// 	int				n_sidedefs;
// 	int				i_sidedefs;
// 	int				n_objects;
// 	int				i_objects;
// 	double			light_level;
// 	double			hold_light;
// 	int				light;
// 	int				slope_floor_id;
// 	int				slope_ceiling_id;
// 	int				slope_ceiling;
// 	double			slope_floor;
// 	int				floor_end;
// 	int				ceiling_end;
// 	int				height_ceiling;
// 	double			height_floor;
// 	int				txt_ceiling;
// 	int				txt_floor;
// 	int				diff_x;
// 	int				diff_y;
// 	int				plane_x;
// 	t_slope			slope;
// 	int				sidedef_bottom[WIDTH];
// 	int				sidedef_top[WIDTH];
// }					t_sector;

// typedef struct		s_lib {
// 	SDL_Surface		**tex_lib;
// 	int				len_tex_lib;
// 	SDL_Surface		**obj_lib;
// 	int				len_obj_lib;
// 	SDL_Surface		**sky_lib;
// 	t_line			*sky_sd;
// 	t_font_lib		font_lib;
// 	int				portal_ceiling;
// 	int				len_sky_lib;
// 	t_sector		*sector;
// 	int				n_sectors;
// 	t_sidedef		*sidedef;
// 	int				len_sidedef;
// 	t_sidedef		*infection;
// 	int				cur_len_infection;
// 	int				tot_len_infection;
// 	t_sprite		*sprites;
// 	int				n_mov_sprites;
// 	t_m_object		*mov_sprites;
// }					t_lib;

// typedef struct		s_gamedesign {
// 	t_sector		*sector;
// 	int				s_len;
// 	int				s_size;
// 	t_sidedef		*sidedef;
// 	int				w_len;
// 	int				w_size;
// 	int				o_len;
// 	int				o_size;
// 	int				cur_sec;
// 	int				cur_sd;
// 	int				portal_sd;
// 	int				portal_sec;
// 	int				pl_pos;
// 	int				pl_x;
// 	int				pl_y;
// 	int				pl_sec;
// 	int				object_bar;
// 	int				sidedef_bar;
// 	SDL_Surface		**sym_lib;
// }					t_gamedesign;

// typedef struct		s_doom {
// 	t_line			tests;
// 	SDL_Window		*window;
// 	SDL_Surface		*surface;
// 	SDL_Event		event;
// 	SDL_Cursor		*cursor;
// 	t_lib			lib;
// 	t_point			pos;
// 	t_event			own_event;
// 	t_gamedesign	game_design;
// 	t_audio			*audio;
// 	t_groceries		*groceries;
// 	t_menu			*menu;
// 	t_hud			*hud;
// 	bool			is_running;
// 	bool			game_editor;
// 	bool			hud_display;
// 	bool			light;
// 	bool			start_timer;
// 	double			player_std_height;
// 	double			player_height;
// 	double			player_width;
// 	int				texture_width;
// 	int				texture_height;
// 	int				i_sidedef;
// 	int				i_sector;
// 	int				prev_sector;
// 	double			ray_angle;
// 	double			dir_angle;
// 	double			ray_adjacent;
// 	double			distance;
// 	double			horizontal_plane_dist;
// 	int				obj_height;
// 	double			max_ray;
// 	double			dist_to_plane;
// 	int				visible_sprites;
// 	int				difficulty;
// 	int				total_sprites;
// 	t_line			level_exit;
// 	double			stripe_distance[WIDTH];
// 	t_prev_sidedef	prev_sidedef;
// 	int				save_poster;
// 	int 			game_time;
// 	int				game_start_time;
// 	int				save_scissor_lift;
// }					t_doom;

// #endif