/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/09 12:13:52 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# include "audio.h"

# include "../sdl/includes/SDL.h"

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

# define PLAYER_HEIGHT 32
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
	double			height_standard;
	int				wall_offset;
	t_point			intersect;
}					t_plane;

typedef struct		s_sidedef {
	int				id;
	t_line			line;
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
	t_point			intersect;
}					t_sidedef;

typedef struct		s_sector {
	int				id;
	int				outside;
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
	int				diff_x;
	int				diff_y;
}					t_sector;

typedef struct		s_lib{
	SDL_Surface		**tex_lib;
	int				len_tex_lib;
	SDL_Surface		**obj_lib;
	int				len_obj_lib;
	SDL_Surface		**sky_lib;
	int				len_sky_lib;
	t_line			*sky_sd;
	t_sector		*sector;
	t_sidedef		*sidedef;
	t_object		*sprites;
	int				n_mov_sprites;
	t_m_object		*mov_sprites;
}					t_lib;

typedef struct		s_gamedesign{
		t_sector	*sector;
		int			s_len;
		int			s_size;
		t_sidedef	*sidedef;
		int			w_len;
		int			w_size;
		int			cur_sec;
		int			cur_sd;
		int			portal_sd;
		int			portal_sec;
		int 		pl_pos;
		int			pl_x;
		int			pl_y;
		int			pl_sec;
}
					t_gamedesign;

typedef struct		s_doom {
	int				is_running;
	int				game_editor;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Surface		**textures;
	SDL_Event		event;
	t_lib			lib;
	t_point			pos;
	t_event			own_event;
	int				wall_height_std;
	double			player_std_height;
	double			player_height;
	int				texture_width;
	int				texture_height;
	int				i_sector;
	int				prev_sector;
	double			ray_angle;
	double			dir_angle;
	double			ray_adjacent;;
	int				obj_height;
	double			max_ray;
	double			dist_to_plane;
	t_gamedesign	game_design;
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

/*read functions*/
SDL_Surface			**save_img(int fd, int *len);
SDL_Surface			**save_sky(t_line **sky_sd);
void				error(char *error, int line_num);
int					open_file(char *filename);
t_bmp				*malloc_images_lib(int len);
SDL_Surface			**malloc_sdl_lib(t_bmp *images, int len);
t_sector			*save_sectors(int fd, int *len);
t_sidedef			*save_walls(int fd);
t_object			*save_sprites(int fd);
void				save_libraries(t_doom *doom);
void				add_inf_to_lib(t_lib *col_lib, int len, int fd);
int					get_line(char **line, int fd, char *error, int is_num);
t_bmp				*malloc_images_lib(int len);
SDL_Surface			**malloc_sdl_lib(t_bmp *images, int len);
int					open_file(char *filename);
int					line_num(int i);

/*events functions*/
void				key_press(t_doom *doom, t_event *event,\
						SDL_KeyboardEvent *key);
void				key_release(t_event *event, SDL_KeyboardEvent *key);
void				key_handler(t_doom *doom, t_event *event, double dt);
void				mouse_press(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				mouse_release(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				camera_movement(t_doom *doom,\
						SDL_MouseMotionEvent *motion, double dt);
void				move_cam_direction(t_doom *doom,\
						SDL_MouseMotionEvent *motion, double dt);
void				cam_move_fb(t_doom *doom, double dt, int direction);
void				cam_move_rl(t_doom *doom, double dt, int direction);
int					check_floor_diff(t_doom *doom, int sector, int next_sector);
void				jump_player(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);

/*render functions*/
int					sidedef_render(t_doom *doom, t_ray ray,\
						int sector, int prev_sector);
int					project_on_plane(t_doom *doom, t_sidedef sidedef, int x);
void    			set_texture_properties(t_doom *doom, t_sector sector,\
						int texture);
int					set_properties_slope(t_doom *doom, t_sidedef sidedef,\
						t_plane *plane);
void				draw_onesided_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_portal_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_skybox(t_doom *doom, int x, t_sidedef sidedef,\
						t_plane plane);
void		    	draw_ground(t_doom *doom, int x, int y);
void		  		draw_sky(t_doom *doom, int x, int y);
void				draw_ceiling(t_doom *doom, int x, t_sector sector, int y);
void				draw_floor(t_doom *doom, int x, t_sector sector, t_plane plane);
void				put_pixel(t_doom *doom, int x, int y, int color);
void				put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,\
						Uint32 pixel_dex);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point				line_delta(t_point start, t_point end);
double				point_distance(t_point p1, t_point p2, double angle);
double				point_line_distance(t_point point, t_line line);
double				sidedef_intersection_distance(t_ray ray, t_line line, t_point *intersect);
void				wall_offset(t_plane *plane, int sidedef_top);
void				find_side(t_doom *doom, int x, t_line line, t_plane plane, t_point intersect);
void				sidedef_render_skybox(t_doom *doom, t_ray ray, t_line *sky_sd);
Uint8				find_slope_line_offset(t_point start, t_point end);

/*game editor*/

void    open_game_editor(t_doom *doom);
void	add_sidedef(t_doom *doom, int x, int y);
void	del_sidedef(t_doom *doom);
void	add_sector(t_doom *doom);
void	del_sector(t_doom *doom);
void    draw_bar(Uint32 **pixels, t_bar bar);
void    draw_bar_point(Uint32 **pixels, t_bar bar);
void	add_portal(t_doom *doom, int dir);
void    add_to_game(t_doom *doom);
void	mouse_press_game_editor(t_doom *doom, int x, int y);
void    bars(Uint32 **pixels, t_doom *doom);
#endif
