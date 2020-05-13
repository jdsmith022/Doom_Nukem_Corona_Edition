#ifndef DOOM_NUKEM_H
#define DOOM_NUKEM_H
# include "libft/libft.h"
#define NUM_LEVELS 1

typedef struct	s_exture {
	int 			width;
	int 			height;
	char			*address;
	int				b_p_p;
	int				size_line;
	int				endian;
	int				repeat;
	int				max_repeat;
}				t_exture;

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

typedef struct			s_plane
{
	double				sidedef_top;
	double				sidedef_bottom;
	double				mid_texture_top;
	double				mid_texture_bottom;
}						t_plane;

typedef struct			s_sidedef {
	int					portal;
	t_point				start;
    t_point				end;
	int					action;
	int					sector;
	int					opp;
//	int					opp_sector;
//	double				offset_x;
//	double				offset_y;
	int					texture_1;
	int					texture_2;
	int					texture_3;
//	double				distance;
}						t_sidedef;

typedef struct			s_sector {
	int					id;
	int					n_sidedefs;
	int					n_objects;
	int					start_obj;
	int					end_obj;
	int					start_walls;
	int					end_walls;
	int					light_level;
	int					height_floor;
	int					height_ceiling;
	int					slope_floor;
	int					slope_ceiling;
	int					texture_ceiling;
	int					texture_floor;
}						t_sector;

typedef struct	s_lib{
	t_exture *tex_lib;
	t_exture *obj_lib;
	t_sector *sector;
	t_sidedef *walls;
	t_object *sprites;
	int		n_mov_sprites;
	t_m_object *mov_sprites;
}				t_lib;


t_exture   *save_img(int fd);
void    error(char *error, int line_num);
t_sector   *save_sectors(int fd, int *len);
t_sidedef  *save_walls(int fd);
t_object  *save_sprites(int fd);
void    add_inf_to_lib(t_lib *col_lib, int len, int fd);
int     get_line(char **line, int fd, char *error, int is_num);


#endif