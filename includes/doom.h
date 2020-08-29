#ifndef DOOM_H
# define DOOM_H

# include <stdio.h> //remove
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <time.h>

# include "../libft/libft.h"
# include "../bmp/srcs/bmp.h"
# include "../srcs/editor/game_editor.h"
# include "font.h"
# include "struct.h"

# include "../sdl/includes/SDL.h"

// # define NAME "Doom Nukem Corona Edition"

// # define TRUE 1
// # define FALSE 0

// # define NUM_LEVELS 1

// # define INIT_ERR	"error: initialization of SDL"
// # define MALLOC_ERR "error: malloc"
// # define OPEN_ERR	"error: opening file"
// # define FONT_ERR	"error: writing font to screen"

// # define WIDTH 800
// # define HEIGHT 600

// # define STD_TEXT_HEIGHT 96

// # define PI 3.14159265359

// # define PLAYER_HEIGHT 50
// # define MOVE_SPEED 100
// # define SENSITIVITY 0.9
// # define GRAVITY -2
// # define VELOCITY  5

// # define RED 1
// # define GREEN 2
// # define BLUE 3
// # define FONT_MASK 0X36
// # define WINDOW_MASK 0XFF

// # define SLOPE_COLOR 0X505052

// # define SECTORS		doom->lib.sector
// # define SIDEDEFS		doom->lib.sidedef
// # define TEXTURES		doom->lib.tex_lib
// # define SPRITES		doom->lib.sprites
// # define OBJ_LIB		doom->lib.obj_lib

// # define OUTSIDE 1
// # define EXIT_LEVEL 2
// # define START_SECTOR 3
// # define START_TIMER 4
// # define CHECKOUT 5

// # define WINDOW 6

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;
typedef struct s_menu		t_menu;
typedef struct s_hud		t_hud;

// typedef enum			e_gamestate
// {
// 	updated,
// 	changed
// }						t_gamestate;

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
// 	int					index;
// 	int					amount;
// 	t_point				pos;
// 	t_point				sprite_begin;
// 	double				size;
// 	t_line				*lines;
// 	int					action;
// 	int					*textures;
// 	int					block;
// 	int					sector;
// 	int					n_sector;
// 	double				width;
// 	double				height;
// 	double				sprite_x;
// 	double				sprite_y;
// 	int					visible;
// 	double				distance;
// 	int					prev_sectors[50];
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
// 	bool			mouse_pointer;
// 	bool			set_step;
// 	int				sliding_door;
// 	int				hold_angle;
// 	int				hold_x;
// 	int				hold_y;
// 	int				move_pos_f;
// 	int				move_pos_b;
// 	int				move_pos_l;
// 	int				move_pos_r;
// 	int				floor_diff;
// 	int				ceiling_diff;
// 	int				next_sector_height;
// 	int				step_down;
// 	double			velocity;
// 	int				y_pitch;
// 	int				virus_hit_index;
// 	bool			virus_red;
// 	int				virus_red_i;
// 	bool			corona_hit;
// 	bool			scissor_lift;
// 	bool			scissor_lift_up;
// 	bool			scissor_lift_down;
// 	bool			parked_too_close;
// 	bool			fall;
// 	bool			mist;
// 	bool			spray_mist;
// 	bool			trolly;
// 	bool			light_switch;
// 	bool			light_switch_changed;
// 	bool			refill;
// 	bool			action;
// 	bool			spray_shopper;
// 	bool			sprite_collision;
// 	bool			toilet_paper;
// 	bool			window;
// 	int				sprite_collision_dist;
// 	int				sprite_index;
// 	struct timespec	light_time;
// 	double			hold_light;
// 	int				hold_light_sector;
// 	int				click_light;
// 	int				fall_count;
// 	bool			groc_pickup;
// 	bool			died;
// 	int				sanitizer_refills;
// 	struct timespec	refill_pause;
// 	struct timespec	sprite_timer;
// }					t_event;

// typedef struct		s_object
// {
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
// 	int				x;
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

// typedef struct		s_window {
// 	int				index;
// 	int				x_start;
// 	int				x_end;
// 	int				y_pixel_top[WIDTH];
// 	int				y_pixel_bottom[WIDTH];
// 	double			height_standard[WIDTH];
// 	int				wall_offset[WIDTH];
// 	double			sidedef_offset[WIDTH];
// 	int				opp_sector;
// 	int				curr_sector;
// }					t_window;

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
// 	double			angle;
// 	int				poster;
// 	t_prev_sidedef	prev_sidedef;
// }					t_sidedef;

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
// 	double			slope_ceiling;
// 	double			slope_floor;
// 	int				floor_end;
// 	int				ceiling_end;
// 	double			height_ceiling;
// 	double			height_floor;
// 	int				txt_ceiling;
// 	int				txt_floor;
// 	int				diff_x;
// 	int				diff_y;
// 	int				sidedef_bottom[WIDTH];
// 	int				sidedef_top[WIDTH];
// 	int				sidedef_mid_bottom[WIDTH];
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
// 	t_window		window;
// 	int				*sprite_order;
// }					t_lib;

// typedef struct		s_gamedesign {
// 	t_sector		*sector;
// 	int				s_len;
// 	int				s_size;
// 	t_sidedef		*sidedef;
// 	int				w_len;
// 	int				w_size;
// 	t_sprite		*object;
// 	int				o_len;
// 	int				o_size;
// 	int				cur_tex;
// 	int				cur_sec;
// 	int				cur_sd;
// 	int				cur_obj;
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

// typedef struct		s_render
// {
// 	t_sidedef		near_sidedef;
// 	t_point			intersect;
// 	double			distance;
// 	double			min_distance;
// }					t_render;

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
// 	int				game_state;
// 	bool			is_running;
// 	bool			game_editor;
// 	bool			hud_display;
// 	bool			light;
// 	bool			start_timer;
// 	double			player_std_height;
// 	double			player_height;
// 	double			cam_slope_height;
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
// 	double			stripe_distance[WIDTH];
// 	t_prev_sidedef	prev_sidedef;
// 	int				save_poster;
// 	int				game_time;
// 	struct timespec	game_start_time;
// 	int				save_scissor_lift;
// 	int				up;
// }					t_doom;

/*core functions*/
int					main(void);
void				game_init(t_doom *doom);
void				doom_init(t_doom *doom);
void				sdl_init(t_doom *doom);
void				init_menu(t_doom *doom);
void				init_hud(t_doom *doom);
void				init_events(t_event *event);
void				init_audio(t_doom *doom);
void				game_loop(t_doom *doom);
void				doom_update(t_doom *doom, double dt_time);
void				doom_render(t_doom *doom);

double				point_distance(t_point p1, t_point p2);
double				point_distance_angle(t_point p1, t_point p2, double angle);
t_point				check_line_intersection(t_line line1, t_line line2);
double				get_line_angle(t_line line);
double				point_line_distance(t_point point, t_line line);
t_point				line_delta(t_point start, t_point end);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);

void				timer(t_doom *doom);
double				get_timeframe(long *last_frame_time);
void				update_hud_ui(t_doom *doom);
void				doom_exit_success(t_doom *doom);
void				doom_exit_failure(t_doom *doom, const char *exit_message);
void				doom_exit_lib_failure(t_bmp *bmp, const char *exit_meassge);
void				doom_exit_read_failure(t_doom *doom, \
						const char *exit_message, int line);
void				free_sdl_lib(t_doom *doom);
void				free_struct_lib(t_doom *doom);
int					line_num(int i);

/*game editor*/
void				open_game_editor(t_doom *doom);
void				add_sidedef(t_doom *doom, int x, int y);
void				del_sidedef(t_doom *doom);
void				add_sector(t_doom *doom);
void				del_sector(t_doom *doom);
void				draw_bar(t_doom *doom, Uint32 **pixels, t_bar bar);
void				draw_bar_point(t_doom *doom, Uint32 **pixels, t_bar bar);
void				add_portal(t_doom *doom, int dir);
void				add_to_game(t_doom *doom);
void				mouse_press_game_editor(t_doom *doom, int x, int y);
void				printing_map(t_gamedesign *design);
void				bars(Uint32 **pixels, t_doom *doom);
void				draw_images(Uint32 *pixels, t_doom *doom);
void				draw_screen_colors(Uint32 *pixels, t_doom *doom);
void				box_in_sectors(t_doom *doom);
void				init_game_design(t_doom *doom);
void				init_game_design(t_doom *doom);
void				draw_lines(t_doom *doom, Uint32 **pixels, int b);
void				add_object(t_doom *doom, int x, int y);
void				draw_object(t_doom *doom, Uint32 **pixels);
void				draw_lines(t_doom *doom, Uint32 **pixels, int b);
void				del_obj(t_doom *doom);
void				add_specifications(t_doom *doom, int index);
void				add_obj_lines(int x, int y, t_doom *doom, int index);
void				coor_pos(t_doom *doom);

#endif