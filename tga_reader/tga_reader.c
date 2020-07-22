#include "../includes/doom.h"


// void		read_tga_header(t_tga *tga, uint8_t *file)
// {
// 	tga->header.id_length = file[0];
// 	tga->header.color_map_type = file[1];
// 	tga->header.data_type = file[2];
// 	tga->header.colormap_origin = file[3];
// 	tga->header.colormap_len = file[4];
// 	tga->header.colormap_size = fd[5];
// 	tga->header.x_origin = file[9] << 8 | file[8];
// 	tga->header.y_origin = file[11] << 8 | file[10];
// 	tga->header.width = file[13] * 256 + file[12];
// 	tga->header.height = file[15] * 256 + file[14];
// 	tga->header.bitsperpixel = file[16];
// 	tga->header.imagedescriptor = file[11];
// 	tga->header.pitch = tga->header.width * (tga->header.bitsperpixel / 8);
// }

static void		tga_exit(t_doom *doom, uint8_t *file)
{
	ft_strdel(file);
	doom_exit_failure(doom, TYPE_ERR);//free and bzero tga
}

t_tga			tga_reader(t_doom *doom, int fd)
{
	t_tga	tga;
	uint8_t	*file;
	ssize_t	ret;
	uint8_t *de_compressed;
    uint8_t *is_compressed;
	
	ret = read_file((char**)&file, fd);
	if (file == NULL)
		doom_exit_failure(doom, TGA_ERR);
	de_compressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	is_compressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	ft_bzero(&tga.header, sizeof(tga.header));
	read_tga_header(&tga, file);
	if (tga.header.data_type != 2)
		tga_exit(doom, file);
	if (tga.header.bitsperpixel != 24 || tga.header.bitsperpixel != 32)
		tga_exit(doom, file);
	return (tga);
}
