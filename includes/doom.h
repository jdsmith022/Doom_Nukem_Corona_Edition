/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 18:12:47 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <time.h>

# include "../libft/libft.h"
# include "../bmp/srcs/bmp.h"
# include "font.h"
# include "struct.h"

# include "../sdl/includes/SDL.h"

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;
typedef struct s_menu		t_menu;
typedef struct s_hud		t_hud;

int					main(int argc, char **argv);
void				game_init(t_doom *doom);
void				doom_init(t_doom *doom);
void				sdl_init(t_doom *doom);
void				init_menu(t_doom *doom);
void				init_hud(t_doom *doom);
void				init_events(t_event *event);
void				init_audio(t_doom *doom);
void				init_player_sprite(t_doom *doom);
void				init_window(t_doom *doom);
void				init_clipping(t_doom *doom);
void				game_loop(t_doom *doom);
void				set_to_window(t_doom *doom);
double				get_timeframe(long *last_frame_time);
void				doom_update(t_doom *doom, double dt_time);
void				sdl_poll_events(t_doom *doom, double dt);
void				update_screen(t_doom *doom);
void				doom_render(t_doom *doom);

double				point_distance(t_point p1, t_point p2);
double				point_distance_angle(t_point p1, t_point p2, double angle);
t_point				check_line_intersection(t_line line1, t_line line2);
double				get_line_angle(t_line line);
double				point_line_distance(t_point point, t_line line);
t_point				line_delta(t_point start, t_point end);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);

void				doom_exit_success(t_doom *doom);
void				doom_exit_failure(t_doom *doom, const char *exit_message);
void				doom_exit_lib_failure(t_bmp *bmp, const char *exit_meassge);
void				doom_exit_read_failure(t_doom *doom, \
						const char *exit_message, int line);
void				free_sdl_lib(t_doom *doom);
void				free_struct_lib(t_doom *doom);
void				free_lists(t_doom *doom);
void				free_clip_lists(t_doom *doom);
int					line_num(int i);

#endif
