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

typedef struct s_audio		t_audio;
typedef struct s_groceries	t_groceries;
typedef struct s_menu		t_menu;
typedef struct s_hud		t_hud;

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

double				get_timeframe(long *last_frame_time);
void				update_screen(t_doom *doom);
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