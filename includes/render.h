#ifndef RENDER_H
# define RENDER_H

# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
# include <sys/stat.h>

# include "../bmp/srcs/bmp.h"
# include "doom.h"

# include "../sdl/includes/SDL.h"

typedef struct s_doom		t_doom;
typedef struct s_line		t_line;
typedef struct s_sector		t_sector;
typedef struct s_plane		t_plane;
typedef struct s_sidedef	t_sidedef;
typedef struct s_lib		t_lib;
typedef struct s_point		t_point;
typedef struct s_ray		t_ray;
typedef struct s_point		t_point;
typedef struct s_line		t_line;

/*render functions*/
void				sidedef_render(t_doom *doom, t_ray ray,\
						int sector, int prev_sector);
t_point				line_intersection(t_point start1, t_point delta1,
							t_point start2, t_point delta2);
t_point				line_delta(t_point start, t_point end);
double				point_distance(t_point p1, t_point p2, double angle);
double				point_line_distance(t_point point, t_line line);
double				sidedef_intersection_distance(t_ray ray, t_line line,\
						t_point *intersect);
void				set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
						t_point intersect, t_doom *doom);

void				project_on_plane(t_doom *doom, t_sidedef sidedef, int x);
void				set_properties_plane(t_doom *doom, t_sidedef sidedef,\
						t_plane *plane, t_sector *sector);
void				set_properties_plane_sidedef(t_doom *doom,\
						t_sidedef sidedef, t_sector *sector, t_plane *plane);
void				set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
						t_sector *opp_sector, t_plane *plane);
t_sidedef			set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom);
void				wall_offset(t_plane *plane, int sidedef_top);

void				slope_plane_settings(t_doom *doom, t_sidedef sidedef,
						t_sector *sector, int flag);
//void				set_slope_bottom_values(t_doom *doom,\
						t_sidedef sidedef, t_sector *sector);
double				set_slope_delta(t_doom *doom, t_sector *sector, int y);
t_sidedef			get_other_side_of_line(t_doom *doom,\
						t_sidedef sidedef, t_sector sector);
int					get_opp_side_of_slope(t_sector sector, int slope_id);
t_point				get_connecting_point(t_line sidedef, t_line conn_sidedef);

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
void				light_floor_ceiling(t_doom *doom, t_sector sector,\
						int x, int y);

double				clamp_angle(double angle);
t_ray				init_ray(t_doom *doom, int x);

#endif