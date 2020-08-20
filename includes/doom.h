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
// # include "struct.h"
// # include "render.h"

# include "../sdl/includes/SDL.h"
# include "../SDL2_ttf.framework/Headers/SDL_ttf.h"

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

# define PI 3.14159265359
# define FOV 60 * (PI / 180)

# define PLAYER_HEIGHT 50
# define MOVE_SPEED 200
# define SENSITIVITY 0.4
# define GRAVITY -2
# define VELOCITY  5

# define Y_CHANGE 1.0 / (float)HEIGHT
# define X_CHANGE 1.0 / (float)WIDTH

# define SECTORS		doom->lib.sector
# define SIDEDEFS		doom->lib.sidedef
# define TEXTURES		doom->lib.tex_lib
# define SPRITES		doom->lib.sprites
# define OBJ_LIB		doom->lib.obj_lib

# define OUTSIDE 1
# define EXIT_LEVEL 2
# define START_SECTOR 3
# define START_TIMER 4
# define CHECKOUT 5

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;
typedef struct s_menu		t_menu;
typedef struct s_hud		t_hud;

# pragma pack(push, 1)

typedef struct			s_rgb {
	char				r;
	char				g;
	char				b;
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
	int					index;			//start index
	int					amount;			//which side is viewed how many textures does the sprite have?
	t_point				pos;
	t_point				sprite_begin;
	double				size;			//products: 16, shopper: 48
	t_line				*lines;
	// double				angle;			//GEBRUIK IK NIET what is the angle on the map
	int					action;	//1 health green, 2 health red, 3 facemask, 4 virus green + placement, 5 virus red + placement, 6 inactive virus 7 scissor lift, 8 inactive health sprite 9 shopper
	int					*textures;		//index to texture, +0, +1, +2 or +3
	int					block;			//can the player walk through it or not
	int					sector;
	int					n_sector; //amount of checked sector stored in prev_sectors
	double				width;
	double				height;
	double				sprite_x;		//x cord translated to viewer space
	double				sprite_y;		//y cord translated to viewer space
	int					visible;		//this is only turned on for the drawing... can't use it for other options
	double				distance;
	// int					face;
	int					prev_sectors[50];	//where to empty them again? don't forget to protect
}						t_sprite;

typedef struct		s_ray {
	t_line			line;
	double			angle;
	double			plane_x;
	int				filter;
}					t_ray;

typedef struct		s_event {
	bool			mouse_press;
	bool			mouse_state_switched;
	bool			jump;
	bool			bend;
	bool			select;
	bool			shoot;
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
	int				virus_hit_index;
	bool			virus_red;
	int				virus_red_i;
	bool			scissor_lift;
	bool			scissor_lift_up;
	bool			scissor_lift_down;
	bool			parked_too_close;
	bool			fall;
	bool			mist;
	bool			spray_mist;
	bool			trolly;
	bool			light_switch;
	bool			refill;
	bool			action;
	bool			spray_shopper;
	bool			sprite_collision;
	bool			toilet_paper;
	int				sprite_collision_dist;
	int				sprite_index;
	struct timespec	light_time;
	double			hold_light;
	int				hold_light_sector;
	int				click_light;
	int				fall_count;
	bool			groc_pickup;
	bool			died;
	int				sanitizer_refills;
	struct timespec	refill_pause;
}					t_event;

typedef struct		s_m_object{
	int				amount;
	int*			textures;
	int*			face_ang;
	char*			name;
	int				action;
	t_line*			movement;
	// t_line			height;
	int				speed;
	int				spawn_time;
}					t_m_object;

typedef struct		s_object{
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

typedef struct		s_sidedef {
	t_point			intersect;
	t_line			line;
	int				id;
	int				action;
	int				sector;
	int				opp_sidedef;
	int				opp_sector;
	double			offset;
	int				dir;
	int				txt_1;
	int				txt_2;
	int				txt_3;
	double			distance;
	int				infection;
	int				poster;
	t_prev_sidedef	prev_sidedef;
}					t_sidedef;

typedef	struct		s_slope {
	double			distance;
	double			height;
	double			bottom_height;
	int				bottom_plane;
	double			dist_to_bottom;
	int				opp_side;
	int				sidedef_id;
	int				prev_floor_id;
	int				prev_ceiling_id;
	double			delta_height;
	t_point			intersect;
	t_point			prev_intersect;
	t_point			conn_point;
}					t_slope;

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
	int				slope_ceiling;
	double			slope_floor;
	int				floor_end;
	int				ceiling_end;
	int				height_ceiling;
	double			height_floor;
	int				txt_ceiling;
	int				txt_floor;
	int				diff_x;
	int				diff_y;
	int				plane_x;
	t_slope			slope;
	int				sidedef_bottom[WIDTH]; //for cutting sprites
	int				sidedef_top[WIDTH]; //for clipping sprites
	int				sidedef_mid_bottom[WIDTH]; //for clipping sprites
}					t_sector;

typedef struct		s_lib {
	SDL_Surface		**tex_lib;
	int				len_tex_lib;
	SDL_Surface		**obj_lib;
	int				len_obj_lib;
	SDL_Surface		**sky_lib;
	t_line			*sky_sd;
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
	int				n_mov_sprites;
	t_m_object		*mov_sprites;
}					t_lib;

typedef struct		s_gamedesign {
	t_sector		*sector;
	int				s_len;
	int				s_size;
	t_sidedef		*sidedef;
	int				w_len;
	int				w_size;
	int				o_len;
	int				o_size;
	int				cur_sec;
	int				cur_sd;
	int				portal_sd;
	int				portal_sec;
	int				pl_pos;
	int				pl_x;
	int				pl_y;
	int				pl_sec;
	int				object_bar;
	int				sidedef_bar;
	SDL_Surface		**sym_lib;
}					t_gamedesign;

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
	bool			is_running;
	bool			game_editor;
	bool			hud_display;
	bool			light;
	bool			start_timer;
	double			player_std_height;
	double			player_height;
	double			cam_slope_height;
	double			player_width;
	int				texture_width;
	int				texture_height;
	int				i_sidedef;
	int				i_sector;
	int				prev_sector;
	double			ray_angle;
	double			dir_angle;
	double			ray_adjacent;
	double			distance;
	double			horizontal_plane_dist;
	int				obj_height;
	double			max_ray;
	double			dist_to_plane;
	int				visible_sprites;
	int				difficulty;
	int				total_sprites;
	double			stripe_distance[WIDTH];
	t_prev_sidedef	prev_sidedef;
	int				save_poster;
	int				game_time;
	int				game_start_time;
	int				save_scissor_lift;
	int				up;
}					t_doom;

/*core functions*/
int					main(void);
void				game_init(t_doom *doom);
void				doom_init(t_doom *doom);
int					sdl_init(t_doom *doom);
void				init_menu(t_doom *doom);
void				init_hud(t_doom *doom);
void				game_loop(t_doom *doom);
void				doom_update(t_doom *doom, double dt_time);
void				doom_render(t_doom *doom);
double				points_distance(t_point p1, t_point p2);
t_point				check_line_intersection(t_line line1, t_line line2);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point				line_delta(t_point start, t_point end);
double				point_distance(t_point p1, t_point p2, double angle);
double				point_line_distance(t_point point, t_line line);
void				timer(t_doom *doom);
double				get_timeframe(long *last_frame_time);
void				update_hud_ui(t_doom *doom);
void				doom_exit_success(t_doom *doom);
void				doom_exit_failure(t_doom *doom, const char *exit_message);
void				doom_exit_lib_failure(t_bmp *bmp, const char *exit_meassge);
void				free_sdl_lib(t_doom *doom);
void				free_struct_lib(t_doom *doom);

/*read functions*/
SDL_Surface			**save_textures(t_doom *doom, int fd, int *len);
SDL_Surface			**save_objects(t_doom *doom, int fd, int *len);
SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd);
void				error(char *error, int line_num);
int					open_file(char *filename);
t_sector			*save_sectors(t_doom *doom, int fd, int *len);
t_sidedef			*save_walls(t_doom *doom, int fd, int *len);
t_sprite			*save_sprites(t_doom *doom, int fd, int *total_sprites);
void				save_bpm_to_sdl(t_doom *doom, t_bmp *images,\
						SDL_Surface **lib, int index);
void				save_libraries(t_doom *doom);
void				add_inf_to_lib(t_doom *doom, t_lib *col_lib,\
						int len, int fd);
int					get_line(char **line, int fd, char *error, int is_num);
void				set_texture_type(t_doom *doom, const char *name,\
						SDL_Surface *surface);
t_bmp				*malloc_images_lib(t_doom *doom, int len);
SDL_Surface			**malloc_sdl_lib(t_doom *doom, t_bmp *images, int len);
int					open_file(char *filename);
int					line_num(int i);
t_sprite			object_inf(int fd, int sector, int obj_len);
t_sidedef			wall_inf(int fd, int sector, int tex_len, int sec_len);
t_sector			sector_inf(int fd, int tex_len);

/*events functions*/
void				key_press(t_doom *doom, t_event *event,\
						SDL_KeyboardEvent *key);
void				key_release(t_event *event, SDL_KeyboardEvent *key);
void				key_handler(t_doom *doom, t_event *event, double dt);
void				mouse_press(t_doom *doom,\
						SDL_MouseButtonEvent *button, t_event event);
void				mouse_release(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				camera_movement(t_doom *doom,\
						SDL_MouseMotionEvent *motion, double dt);
void				move_cam_direction(t_doom *doom,\
						SDL_MouseMotionEvent *motion,\
						double dt, t_event *event);
void				set_new_position(t_doom *doom, t_event *event, double dt);
int					check_floor_diff(t_doom *doom, int sector, int next_sector);
int					check_sector_height_diff(t_doom *doom,\
						int sector, int next_sector);
bool				handle_mouse_state(t_doom *doom);

/*render functions*/
void				sidedef_render(t_doom *doom, t_ray ray,\
						int sector, int prev_sector);
double				sidedef_intersection_distance(t_ray ray, t_line line,\
						t_point *intersect);
void				set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
						t_point intersect, t_doom *doom);

void				project_on_plane(t_doom *doom, t_sidedef sidedef, int x);
void				set_properties_plane(t_doom *doom, t_sidedef sidedef,\
						t_plane *plane, t_sector *sector);
void				set_properties_plane_sidedef(t_doom *doom,\
						t_sidedef sidedef, t_sector sector, t_plane *plane);
void				set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
						t_sector opp_sector, t_plane *plane);
t_sidedef			set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom);
double				set_slope_height(t_doom *doom, t_sidedef sidedef,\
						t_sector sector);
void				wall_offset(t_plane *plane, int sidedef_top);
void				set_texture_properties(t_doom *doom);
void				set_floor_limit(t_doom *doom, t_plane *plane,\
						t_sidedef sidedef, t_sector *sector);
void				set_ceiling_limit(t_doom *doom, t_plane *plane,\
						t_sidedef sidedef, t_sector *sector);
Uint8				find_slope_line_offset(t_point start, t_point end);
void				draw_onesided_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_portal_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				put_portal_pixel(t_doom *doom, t_point pixel);
void				draw_window(t_doom *doom, t_plane plane,
						t_sidedef sidedef, int x);
void				row_calculations(t_doom *doom, double dist, Uint32 index,\
						SDL_Surface *lib);
void				put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,\
						Uint32 pixel_dex);
void				draw_ceiling(t_doom *doom, int x, t_sector sector, int y);
void				draw_floor(t_doom *doom, int x, t_sector sector, int y);

void				sidedef_render_skybox(t_doom *doom, t_ray ray,\
						t_line *sky_sd);
void				find_skybox_sidedef_texture(t_doom *doom, int x,\
						t_plane plane);
void				draw_skybox(t_doom *doom, int x, t_sidedef sidedef,\
						t_plane plane);
void				draw_ground(t_doom *doom, int x, int y);
void				draw_sky(t_doom *doom, int x, int y);

void				draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x);
void				draw_texture(SDL_Surface *texture, t_doom *doom, \
						int x, int y);
void				draw_img(SDL_Surface *texture, t_doom *doom, SDL_Rect rect);

void				add_saturation(char *r, char *g, char *b, double light);
void				light_sidedef(t_doom *doom, t_sidedef sidedef, int x);
void				light_floor_ceiling(t_doom *doom, t_sector sector,\
						int x, int y);

double				clamp_angle(double angle);
t_ray				init_ray(t_doom *doom, int x);

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

/*sprite functions*/
void				sprite_init(t_doom *doom);
void				sprite_check(t_doom *doom, t_ray ray, int sector, int prev_sector);
void				sprite_render(t_doom *doom);
int					*sort_sprite_array(t_sprite *sprite, int visible_sprites, int total_sprites);
void				find_position(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index);
void				draw_stripes(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp);
void				sprite_reset(t_doom *doom);
void				scale_sprite(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, t_sprite *sprite);
t_point				sidedef_sprite_intersect(t_line sidedef, t_line sprite);
int					sprite_collision(t_doom *doom, t_line movement);
void				exit_scissor_lift(t_doom *doom);
// void				draw_scissor_lift_bar(t_doom *doom);
// void				draw_spraying_hand(t_doom *doom);
void				put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index, int i, double distance);
void				remove_red_virus(t_doom *doom);
void				add_mist_to_sanitizer(t_doom *doom);
void				draw_player_adds(t_doom *doom);
void				draw_add_on(t_doom *doom, int sprite_i);
// void    			shoot(t_doom *doom);

#endif
