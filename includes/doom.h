/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou          #+#    #+#                */
/*   Updated: 2020/04/06 14:53:18 by Malou         ########   odam.nl         */
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
	double				sidedef_top;
	double				sidedef_bottom;
	double				mid_texture_top;
	double				mid_textur_bottom;
}						t_plane;

typedef struct			s_sidedef {
	t_point				start;
    t_point				end;
	int					action;
	int					sector;
	struct s_sidedef	*opp;
	int					opp_sector;
	double				offset_x;
	double				offset_y;
	char				*texture_1;
	char				*texture_2;
	char				*texture_3;
	double				distance;
}						t_sidedef;

typedef struct			s_sector {
	int					id;
	int					n_sidedefs;
	t_sidedef			sidedef[5]; 
	int					height_floor;
	int					height_ceiling;
	int					light_level;
	char				*texture_ceiling;
	char				*texture_floor;
}						t_sector;

typedef struct			s_doom {
    SDL_Window			*window;
	SDL_Renderer 		*renderer;
	SDL_Surface			*surface;
	SDL_Event			event;
	t_sector			sector[3];
	t_point				pos;
	t_event				own_event;
	int					curr_sector;
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
void					project_on_plane(t_doom *doom, t_sidedef sidedef, int x);

void					draw_ceiling(t_doom *doom, int sidedef_top, int sector, int x);
void					draw_onesided_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_portal_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_sidedef(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void					draw_floor(t_doom *doom, int sector, int x, int y);

t_point					line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point					line_delta(t_point start, t_point end);
double					point_distance(t_point p1, t_point p2, double angle);

#endif
