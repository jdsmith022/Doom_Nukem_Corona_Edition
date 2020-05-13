/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/13 18:32:38 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "../sdl/includes/SDL.h"

# define INIT_ERR	"error: initialization of SDL"
# define MALLOC_ERR "error: malloc"

# define WIDTH 800
# define HEIGHT 600

# define PI 3.14159265359
# define FOV 60 * (PI / 180)

# define SPEED 20

typedef struct			s_point {
    double				x;
    double				y;
}						t_point;

typedef struct			s_line {
    t_point				start;
    t_point				end;
}						t_line;

typedef struct			s_ray {
	t_line				line;
	double				angle;
	double				plane_x;
}						t_ray;

typedef struct			s_event {
	int					mouse_press;
	int					hold_angle;
	int					hold_x;
}						t_event;

typedef struct			s_plane
{
	int					sidedef_top;
	int					sidedef_bottom;
	int					mid_texture_top;
	int					mid_texture_bottom;
	t_point				intersect;
}						t_plane;

typedef struct			s_sidedef {
	int					id;
	t_line				line;
	int					action;
	int					sector;
	int					opp_sidedef;
	int					opp_sector;
	double				offset_x;
	double				offset_y;
	int					*texture_1;
	int					*texture_2;
	int					*texture_3;
	double				distance;
}						t_sidedef;

typedef struct			s_sector {
	int					id;
	int					n_sidedefs;
	int					i_sidedefs;
	int					height_floor;
	int					height_ceiling;
	int					light_level;
	int					slope_id;
	int					slope_angle;
	char				*texture_ceiling;
	char				*texture_floor;
}						t_sector;

typedef struct			s_doom {
  	SDL_Window			*window;
	//SDL_Renderer 		*renderer;
	SDL_Surface			*surface;
	SDL_Event			event;
	t_sector			sector[3];
	t_sidedef			sidedef[13];
	t_point				pos;
	t_event				own_event;
	int					i_sector;
	int					esc;
	double				dir_angle;
	double				ray_adjacent;
	int					wall_width;
	double				wall_height;
	int					obj_height;
	double				max_ray;
	double				dist_to_plane;
}						t_doom;


int						main(void);
void					doom_init(t_doom *doom);
void					game_loop(t_doom *doom);
void					doom_render(t_doom *doom);
void					doom_input(t_doom *doom);
void					sidedef_render(t_doom *doom, t_ray ray,\
							int sector, int prev_sector);
void					project_on_plane(t_doom *doom, t_sidedef sidedef, int x, t_point intersect);
void					set_properties_slope(t_doom *doom, t_sidedef sidedef,\
							int x, t_plane *plane);

void					draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_portal_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_ceiling(t_doom *doom, int x, int sidedef_top);
void					draw_floor(t_doom *doom, int x, int y);
void					put_pixel(t_doom *doom, int x, int y, int color);

t_point					line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point					line_delta(t_point start, t_point end);
double					point_distance(t_point p1, t_point p2, double angle);
double					point_line_distance(t_point point, t_line line);

void 					move_position_forward(t_doom *doom);
void 					move_position_backward(t_doom *doom);
void 					move_position_left(t_doom *doom);
void					move_position_right(t_doom *doom);
int						movement_collision(t_doom *doom, t_line move);
t_point					check_line_intersection(t_line move, t_sidedef sidedef);

void					doom_exit_success(t_doom *doom);
void					doom_exit_failure(t_doom *doom, const char *exit_message);
#endif
