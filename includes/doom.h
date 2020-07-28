#ifndef DOOM_H
# define DOOM_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "../bmp/srcs/bmp.h"
# include "../srcs/editor/game_editor.h"
# include "font.h"

# include "../sdl/includes/SDL.h"
# include "../SDL2_ttf.framework/Headers/SDL_ttf.h"

# define NAME "Doom Nukem Corona Edition"

# define TRUE 1
# define FALSE 0

# define NUM_LEVELS 1

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"

# define WIDTH 800
# define HEIGHT 600

# define PI 3.14159265359
# define FOV 60 * (PI / 180)

# define PLAYER_HEIGHT 48
# define MOVE_SPEED 200
# define CAM_SPEED 5
# define GRAVITY -0.5
# define VELOCITY 12

# define Y_CHANGE 1.0 / (float)HEIGHT
# define X_CHANGE 1.0 / (float)WIDTH

# define SECTORS	doom->lib.sector
# define SIDEDEFS	doom->lib.sidedef
# define TEXTURES	doom->lib.tex_lib

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;

#pragma pack(push, 1)

typedef struct 			t_rgb {
	char				r;
	char				g;
	char				b;
}						t_rgb;

#pragma pack(pop)

typedef struct			s_coord {
	uint16_t			x;
	uint16_t			y;
}						t_coord;

typedef struct			s_hsv{
	double				r;
	double				g;
	double				b;
}						t_hsv;

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
	int					amount;			//which side is viewed
	t_point				pos;
	double				size;			//small: 8, medium: 12, large: 18
	t_line				*lines;
	double				angle;			//GEBRUIK IK NIET what is the angle on the map
	int					action;
	int					*textures;		//index to texture, +0, +1, +2 or +3
	int					*face_ang;		//DIT KAN GEWOON EEN INT ZIJN, dit is dan de index naar de texture
	int					block;			//can the player walk through it or not
	int					sector;
	double				width;
	double				height;
	double				sprite_x;		//x cord translated to viewer space
	double				sprite_y;		//y cord translated to viewer space
	int					visible;
	double				distance;
	int					face;
	double				offset;
	// int					screen_left_x;
	// int					screen_right_x;
	// int					position;
}						t_sprite;

typedef struct		s_ray {
	t_line			line;
	double			angle;
	double			plane_x;
	int				filter;
}					t_ray;

typedef struct		s_event {
	int				mouse_press;
	bool			mouse_state_switched;
	int				hold_angle;
	int				hold_x;
	int				hold_y;
	int				cam_move_f;
	int				cam_move_b;
	int				cam_move_l;
	int				cam_move_r;
	int				floor_diff;
	int				step_down;
	int				jump;
	int				bend;
	int				select;
	double			velocity;
	int				y_pitch;
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
	int				poster;
}					t_sidedef;

typedef struct		s_sector {
	int				id;
	int				outside;
	int				n_sidedefs;
	int				i_sidedefs;
	int				n_objects;
	int				i_objects;
	double			light_level;
	int				light;
	int				slope_id;
	int				slope_ceiling;
	int				slope_floor;
	int				height_ceiling;
	int				height_floor;
	int				txt_ceiling;
	int				txt_floor;
	int				diff_x;
	int				diff_y;
	int				sidedef_bottom[WIDTH];
	int				sidedef_top[WIDTH];
	double			sidedef_distance[WIDTH];
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
	int				portal_floor;
	int				len_sky_lib;
	t_sector		*sector;
	int				n_sectors;
	t_sidedef		*sidedef;
	int				len_sidedef;
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
	int				cur_sec;
	int				cur_sd;
	int				portal_sd;
	int				portal_sec;
	int				pl_pos;
	int				pl_x;
	int				pl_y;
	int				pl_sec;
}					t_gamedesign;

typedef struct		s_doom {
	int				is_running;
	int				game_editor;
	int				hud;
	int				basket;
	int				shopping;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Event		event;
	SDL_Cursor		*cursor;
	t_lib			lib;
	t_point			pos;
	t_event			own_event;
	int				light;
	double			player_std_height;
	double			player_height;
	double			player_width;
	int				texture_width;
	int				texture_height;
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
	t_gamedesign	game_design;
	t_audio			*audio;
	t_groceries		*groceries;
	int				visible_sprites;
	int				total_sprites;
	double			stripe_distance[WIDTH];
	// int				sidedef_bottom[WIDTH];
	// int				sidedef_top[WIDTH];
	int				test;
}					t_doom;

/*core functions*/
int					main(void);
void				doom_init(t_doom *doom);
int					sdl_init(t_doom *doom);
void				game_loop(t_doom *doom);
void				doom_update(t_doom *doom, double dt_time);
void				doom_render(t_doom *doom);
double				points_distance(t_point p1, t_point p2);
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
void				save_bpm_to_sdl(t_bmp *images,\
						SDL_Surface **lib, int index);
void				save_libraries(t_doom *doom);
void				add_inf_to_lib(t_lib *col_lib, int len, int fd);
int					get_line(char **line, int fd, char *error, int is_num);
void				set_texture_type(const char *name, SDL_Surface *surface);
t_bmp				*malloc_images_lib(t_doom *doom, int len);
SDL_Surface			**malloc_sdl_lib(t_doom *doom, t_bmp *images, int len);
int					open_file(char *filename);
int					line_num(int i);

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
void				cam_move_fb(t_doom *doom, double dt, int direction);
void				cam_move_rl(t_doom *doom, double dt, int direction);
int					check_floor_diff(t_doom *doom, int sector, int next_sector);
void				jump_player(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);
bool				handle_mouse_state(t_doom *doom);

/*render functions*/
void				sidedef_render(t_doom *doom, t_ray ray,\
						int sector, int prev_sector);
void				project_on_plane(t_doom *doom, t_sidedef sidedef, int x, t_point intersect);
void				set_texture_properties(t_doom *doom);
int					set_properties_slope(t_doom *doom, t_sidedef sidedef,\
						t_plane *plane);
Uint8				find_slope_line_offset(t_point start, t_point end);
void				set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
					t_point intersect, t_doom *doom);
void				wall_offset(t_plane *plane, int sidedef_top);

void				draw_onesided_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_portal_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
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

void				put_pixel(t_doom *doom, int x, int y, int color);
void				put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,\
						Uint32 pixel_dex);

t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point				line_delta(t_point start, t_point end);
double				point_distance(t_point p1, t_point p2, double angle);
double				point_line_distance(t_point point, t_line line);
double				sidedef_intersection_distance(t_ray ray, t_line line,\
						t_point *intersect);

void				add_saturation(char *r, char *g, char *b, double light);
void				light_floor_ceiling(t_doom *doom, t_sector sector,\
						int x, int y);

void				draw_poster(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x);
void				set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
					t_point intersect, t_doom *doom);
void				draw_texture(SDL_Surface *texture, t_doom *doom, int x, int y);
void				draw_img(SDL_Surface *texture, t_doom *doom, SDL_Rect rect);
double				clamp_angle(double angle);
t_ray				init_ray(t_doom *doom, int x);

/*game editor*/
void				open_game_editor(t_doom *doom);
void				add_sidedef(t_doom *doom, int x, int y);
void				del_sidedef(t_doom *doom);
void				add_sector(t_doom *doom);
void				del_sector(t_doom *doom);
void				draw_bar(Uint32 **pixels, t_bar bar);
void				draw_bar_point(Uint32 **pixels, t_bar bar);
void				add_portal(t_doom *doom, int dir);
void				add_to_game(t_doom *doom);
void				mouse_press_game_editor(t_doom *doom, int x, int y);

void				bars(Uint32 **pixels, t_doom *doom);
void				draw_images(Uint32 *pixels, t_doom *doom);
void				draw_screen_colors(Uint32 *pixels, t_doom *doom);
void				box_in_sectors(t_doom *doom);

/*sprite functions*/
void				sprite_init(t_doom *doom);
void				sprite_check(t_doom *doom, t_ray ray, int x);
void				sprite_render(t_doom *doom);
int					*sort_sprite_array(t_sprite *sprite, int visible_sprites, int total_sprites);
void				find_position(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index);
void				draw_stripes(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp);
void				sprite_reset(t_doom *doom);

/*actions*/
void				sliding_door(t_doom *doom, int sd_index);
void				create_mv_sidedef(t_sidedef **sidedef, int k, int len);
void				relocate_moving_wall(t_point *intersect,\
						t_sidedef *near_sidedef, t_doom *doom, int x);
void				relocate_poster(t_doom *doom, t_sidedef *poster);
int					init_poster(int x, double distance, t_point intersect,\
						t_sidedef *poster);

#endif
