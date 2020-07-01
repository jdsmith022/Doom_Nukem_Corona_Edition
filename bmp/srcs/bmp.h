#ifndef BMP_H
# define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "../libft/src/libft.h"

#pragma pack(push, 1)

typedef struct		s_bmp_header
{
    uint16_t        signature;
    uint32_t        size;
    uint32_t        reserved;
    uint32_t        data_offset;
}					t_bmp_header;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct		s_bmp_info
{
	uint32_t 		info_size;
    uint32_t 		width;
    uint32_t 		height;
    uint16_t 		planes;
    uint16_t 		bits_per_pixel;
    uint32_t 		compression;
    uint32_t 		img_size;
    uint32_t 		xppm;
    uint32_t 		yppm;
    uint32_t 		colors_used;
    uint32_t 		important_colors;
}					t_bmp_info;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct		s_bmp
{
	t_bmp_info		info;
	void			*pixels;
}					t_bmp;

#pragma pack(pop)

void				print_byte(void *byte, uint32_t len);
void				print_meta_data(t_bmp_info info);
void				exit_with_error(const char *message);
t_bmp				read_bmp(int fd);	

#endif
