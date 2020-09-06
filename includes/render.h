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
void				init_sliding_door(t_doom *doom, t_sidedef *sidedef);
void				render_sliding_door(t_doom *doom, t_sidedef *sidedef);
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
double				set_slope_height_floor(t_doom *doom, t_sidedef sidedef,\
						t_sector sector);
double				set_slope_height_ceiling(t_doom *doom, t_sidedef sidedef,\
						t_sector sector);

void				wall_offset(t_plane *plane, int sidedef_top);
void				set_texture_properties(t_doom *doom);
void				set_floor_limit(t_doom *doom, t_plane *plane,\
						t_sidedef sidedef, t_sector *sector);
void				set_ceiling_limit(t_doom *doom, t_sidedef sidedef, \
						t_sector *sector);
Uint8				find_slope_line_offset(t_point start, t_point end);
void				draw_onesided_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_portal_sidedef(t_doom *doom, t_plane plane,\
						t_sidedef sidedef, int x);
void				draw_ceiling(t_doom *doom, int x, t_sector sector, int y);
void				draw_floor(t_doom *doom, int x, t_sector sector, int y);

void				draw_window_as_sprite(t_doom *doom);
void				save_window(t_doom *doom, t_plane plane,
						t_sidedef sidedef, int x);
void				init_window(t_doom *doom);
void				row_calculations(t_doom *doom, double dist, Uint32 index,\
						SDL_Surface *lib);
void				put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,\
						Uint32 pixel_dex);
void				put_pixel_slope(t_doom *doom, int x, int y);
void				put_portal_pixel(t_doom *doom, t_point pixel, int tint, \
						int mask);

void				sidedef_render_skybox(t_doom *doom, t_ray ray,\
						t_line *sky_sd);
void				find_skybox_sidedef_texture(t_doom *doom, int x,\
						t_plane plane);
void				draw_skybox(t_doom *doom, int x, t_sidedef sidedef,\
						t_plane plane);
void				draw_ground(t_doom *doom, int x, int y);
void				draw_sky(t_doom *doom, int x, int y);

int					set_poster(t_doom *doom, int x, double distance, \
						t_point intersect);
void				draw_poster(t_doom *doom, t_plane plane,\
						int poster_index, int x);
void				draw_texture(SDL_Surface *texture, t_doom *doom, \
						int x, int y);
void				draw_img(SDL_Surface *texture, t_doom *doom, SDL_Rect rect);

void				add_saturation(Uint8 *r, Uint8 *g, Uint8 *b, double light);
void				add_light_to_pixel(t_doom *doom, t_sector sector,\
						int x, int y);
void				add_tint_to_color(Uint32 *color, int tint, int mask);

t_ray				init_ray(t_doom *doom, int x);
double				clamp_angle(double angle);
t_clip				*new_clip_start(int sector_id, int x, int y, int sidedef);
void				free_clipping_values(t_doom *doom, t_clip *list);
void				set_values_clipping_sprites(t_doom *doom, t_plane plane,\
					t_sidedef sidedef, int x);
void				set_mid_bottom(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void				set_bottom(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);
void				set_top(t_doom *doom, t_plane plane, t_sidedef sidedef, int x);

#endif
