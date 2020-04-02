/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:18:17 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 11:38:03 by Malou         ########   odam.nl         */
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

typedef struct		s_point {
    int				x;
    int				y;
}					t_point;

typedef struct		s_event {
	int				mouse_press;
	int				hold_angle;
	int				hold_x;
}					t_event;

typedef struct		s_intersect {
	double			x;
	double			y;
	int				texture;
	char			direction;
	double			obj_dist;
	int				sector;
	int				opp_sector;
}					t_intersect;


typedef struct		s_sidedef {
	t_point			start;
    t_point			end;
	int				action;
	int				sector;
	struct s_sidedef		*opp;
	int				opp_sector;
	double			offset_x;
	double			offset_y;
	char			*texture_1;
	char			*texture_2;
	char			*texture_3;
}					t_sidedef;

typedef struct		s_sector {
	int				id;
	int				height_floor;
	int				height_ceiling;
	int				light_level;
	char			*texture_ceiling;
	char			*texture_floor;
}					t_sector;

typedef struct		s_line {
    t_point			start;
    t_point			end;

}					t_line;

typedef struct		s_column
{
	double			y_start;
	double			y_end;
	int				texture;
	int				height;
	double			offset;
	int				x;
}					t_column;

typedef struct		s_form
{
	int				a_ray;
	int				b_ray;
	int				c_ray;
	int				a_obj;
	int				b_obj;
	int				c_obj;
	double			delta_x;
	double			delta_y;
}					t_form;

typedef struct		s_doom {
    SDL_Window		*window;
	SDL_Renderer 	*renderer;
	SDL_Surface		*surface;
	SDL_Event		event;
    t_sidedef		sidedef[10]; 
	t_sector		sector_1;
	int				esc;
	double			dir_angle;
	int				wall_width;
	double			wall_height;
	int				obj_height;
	double			max_ray;
	double			dist_to_plane;
	double			ray_angle;
	t_point			pos;
	t_event			own_event;
}					t_doom;


int					main(void);
void				doom_init(t_doom *doom);
void				game_loop(t_doom *doom);
void				doom_render(t_doom *doom);
void				doom_input(t_doom *doom);
void				find_sidedef(t_doom *doom, t_line ray, double angle, int sector, int column);
void				draw_column(t_doom *doom, t_intersect intersect, int x);

#endif
