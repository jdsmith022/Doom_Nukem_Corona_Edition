/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/27 14:29:08 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>

# include "../libft/libft.h"
#include "../bmp/srcs/bmp.h"

# include "../sdl/includes/SDL.h"

# define NAME "Doom Nukem Corona Edition"

# define TRUE 1
# define FALSE 0

#define NUM_LEVELS 1

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"

# define WIDTH 800
# define HEIGHT 600

# define PI 3.14159265359
# define FOV 60 * (PI / 180)

# define PLAYER_HEIGHT 100
# define MOVE_SPEED 200
# define CAM_SPEED 5
# define GRAVITY -0.5
# define VELOCITY 12

typedef struct		s_point {
	double			x;
	double			y;
}					t_point;

typedef struct		s_line {
	t_point			start;
	t_point			end;
}					t_line;

typedef struct		s_ray {
	t_line			line;
	double			angle;
	double			plane_x;
}					t_ray;

typedef struct		s_event {
	int				mouse_press;
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
	double			velocity;
	int				y_pitch;
}					t_event;

typedef struct		s_texture {
	int 			width;
	int 			height;
	char			*address;
	int				b_p_p;
	int				size_line;
	int				endian;
	int				repeat;
	int				max_repeat;
}					t_texture;

typedef struct		s_m_object{
	int				n_textures;
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
	int				sidedef_top;
	int				sidedef_bottom;
	int				sidedef_height;
	int				mid_texture_top;
	int				mid_texture_bottom;
	t_point			intersect;
}					t_plane;

typedef struct		s_sidedef {
	int				id;
	t_line			line;
	int				action;
	int				sector;
	int				opp_sidedef;
	int				opp_sector;
	double			offset_x;
	double			offset_y;
	double			offset;
	int				txt_1;
	int				txt_2;
	int				txt_3;
	double			distance;
}					t_sidedef;

typedef struct		s_sector {
	int				id;
	int				n_sidedefs;
	int				i_sidedefs;
	int				n_objects;
	int				i_objects;
	int				light_level;
	int				slope_id;
	int				slope_ceiling;
	int				slope_floor;
	int				height_ceiling;
	int				height_floor;
	int				txt_ceiling;
	int				txt_floor;
}					t_sector;

typedef struct			s_lib{
	t_bmp			*tex_lib;
	t_bmp 			*obj_lib;
	t_sector 			*sector;
	t_sidedef 			*sidedef;
	t_object 			*sprites;
	int					n_mov_sprites;
	t_m_object 			*mov_sprites;
}						t_lib;

typedef struct		s_doom {
	int				is_running;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Surface		**textures;
	SDL_Event		event;
	t_lib			lib;
	t_point			pos;
	t_event			own_event;
	int				wall_height_std;
	int				player_height;
	int				i_sector;
	int				prev_sector;
	double			dir_angle;
	double			ray_adjacent;
	int				wall_width;
	double			wall_height;
	int				obj_height;
	double			max_ray;
	double			dist_to_plane;
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

/*read functions*/
t_bmp			*save_img(int fd);
void				error(char *error, int line_num);
t_sector			*save_sectors(int fd, int *len);
t_sidedef			*save_walls(int fd);
t_object			*save_sprites(int fd);
t_lib					main2(void);
void				add_inf_to_lib(t_lib *col_lib, int len, int fd);
int					get_line(char **line, int fd, char *error, int is_num);

/*events functions*/
void				key_press(t_doom *doom, t_event *event, SDL_KeyboardEvent *key);
void				key_release(t_event *event, SDL_KeyboardEvent *key);
void				key_handler(t_doom *doom, t_event *event, double dt);
void				mouse_press(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				mouse_release(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				camera_movement(t_doom *doom,\
						SDL_MouseMotionEvent *motion, double dt);
void				move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion, double dt);
void				cam_move_fb(t_doom *doom, double dt, int direction);
void				cam_move_rl(t_doom *doom, double dt, int direction);
int					check_floor_diff(t_doom *doom, int sector, int next_sector);
void				jump_player(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);

/*render functions*/
void				sidedef_render(t_doom *doom, t_ray ray,\
						int sector, int prev_sector);
void				project_on_plane(t_doom *doom, t_sidedef sidedef, int x,\
						t_point intersect);
int					set_properties_slope(t_doom *doom, t_sidedef sidedef,\
						t_plane *plane);
void				draw_onesided_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_portal_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_ceiling(t_doom *doom, int x, int sidedef_top);
void				draw_floor(t_doom *doom, int x, int y);
void				put_pixel(t_doom *doom, int x, int y, int color);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point				line_delta(t_point start, t_point end);
double				point_distance(t_point p1, t_point p2, double angle);
double				point_line_distance(t_point point, t_line line);

void				load_textures(t_doom *doom);
#endif
