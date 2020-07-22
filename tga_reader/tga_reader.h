#ifndef TGA_READER_H
# define TGA_READER_H

# include "../includes/doom.h"

# define TGA_ERR "error: reading file to tga"
# define TYPE_ERR "error: invalide tga format"

typedef struct	s_doom	t_doom;

typedef struct	s_header
{
	uint32_t	id_length;
	uint32_t	color_map_type;
	uint32_t	data_type;
	uint32_t	colormap_origin;
	uint32_t	colormap_len;
	uint32_t	colormap_size;
	uint32_t	x_origin;
	uint32_t	y_origin;
	uint32_t	width;
	uint32_t	height;
	uint32_t	bitsperpixel;
	uint32_t	pitch;
	char		imagedescriptor;
}				t_header;

typedef struct	s_tga
{
	t_header	header;
	void		*pixel;
}				t_tga;

t_tga			tga_reader(t_doom *doom, int fd);
int				read_file_for_tga(char **file, int fd);

#endif
