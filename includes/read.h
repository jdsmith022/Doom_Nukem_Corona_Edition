/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:51:20 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "doom.h"

SDL_Surface			**save_textures(t_doom *doom, int fd, int *len);
SDL_Surface			**save_objects(t_doom *doom, int fd, int *len);
void				save_player_sprites(t_doom *doom);
SDL_Surface			**save_sky(t_doom *doom, t_line **sky_sd);
SDL_Surface			**read_from_line(t_doom *doom, char *line,
						int map_fd, int len);
int					open_file(t_doom *doom, char *filename);
t_sector			*save_sectors(t_doom *doom, int fd, int *len);
t_sidedef			*save_walls(t_doom *doom, int fd, int *len);
t_sprite			*save_sprites(t_doom *doom, int fd, int *total_sprites);
void				save_bpm_to_sdl(t_doom *doom, t_bmp *images,\
						SDL_Surface **lib, int index);
void				save_libraries(t_doom *doom);
void				add_inf_to_lib(t_doom *doom, int len, int fd);
void				create_sidedef(t_doom *doom, int fd, int len, int i);
void				create_mv_sidedef(t_doom *doom, t_sidedef *sidedef, int i);
int					get_line(t_doom *doom, char **line, int fd, int is_num);
void				set_texture_type(t_doom *doom, const char *name,\
						SDL_Surface *surface);
t_bmp				*malloc_images_lib(t_doom *doom, int len);
SDL_Surface			**malloc_sdl_lib(t_doom *doom, t_bmp *images, int len);
t_sprite			object_inf(t_doom *doom, int fd, int sector, int obj_len);
t_sidedef			wall_inf(t_doom *doom, int fd, int sector, int sec_len);
t_sector			sector_inf(t_doom *doom, int fd, int tex_len);
void				bmp_safe_exit(t_doom *doom, t_bmp *images);
void				modified(t_doom *doom, char *file_name);

#endif
