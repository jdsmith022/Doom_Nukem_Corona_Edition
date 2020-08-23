#ifndef READ_H
# define READ_H

#include "doom.h"

/*read functions*/

SDL_Surface			**save_textures(t_doom *doom, int fd, int *len);
SDL_Surface			**save_objects(t_doom *doom, int fd, int *len);
SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd);
void				error(char *error, int line_num);
int					open_file(char *filename);
t_sector			*save_sectors(t_doom *doom, int fd, int *len);
t_sidedef			*save_walls(t_doom *doom, int fd, int *len);
t_sprite			*save_sprites(t_doom *doom, int fd, int *total_sprites);
void				save_bpm_to_sdl(t_doom *doom, t_bmp *images,\
						SDL_Surface **lib, int index);
void				save_libraries(t_doom *doom);
void				add_inf_to_lib(t_doom *doom, int len, int fd);
void				create_sidedef(t_doom *doom, int fd, int len, int i);
void				create_mv_sidedef(t_doom *doom, t_sidedef *sidedef, int i);
int					get_line(char **line, int fd, char *error, int is_num);
void				set_texture_type(t_doom *doom, const char *name,\
						SDL_Surface *surface);
t_bmp				*malloc_images_lib(t_doom *doom, int len);
SDL_Surface			**malloc_sdl_lib(t_doom *doom, t_bmp *images, int len);
int					open_file(char *filename);
t_sprite			object_inf(int fd, int sector, int obj_len);
t_sidedef			wall_inf(int fd, int sector, int tex_len, int sec_len);
t_sector			sector_inf(int fd, int tex_len);

#endif