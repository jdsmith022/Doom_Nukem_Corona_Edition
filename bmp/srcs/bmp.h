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

typedef struct		s_pixel
{
	uint8_t 		red;
	uint8_t 		green;
	uint8_t 		blue;
}					t_pixel;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct		s_bmp_header
{
    uint16_t signature;
    uint32_t size;
    uint32_t reserved;
    uint32_t data_offset;
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
	t_pixel			*pixels;
}					t_bmp;

#pragma pack(pop)

void				print_bytes(uint8_t *bytes, unsigned int len);
void				print_meta_data(t_bmp_info info);
void				print_pixel(t_pixel pixel);
void				exit_with_error(const char *message);
t_bmp				read_bmp(int fd);	

#endif
