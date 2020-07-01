#include "bmp.h"

void				exit_with_error(const char *message){
	ft_putstr_fd(message, 2);
	exit(1);
}

void				print_meta_data(t_bmp_info info)
{
	printf("\ninfo size : %u\n", info.info_size);
	printf("width     : %u\n", info.width);
	printf("height    : %u\n", info.height);
	printf("planes    : %u\n", info.planes);
	printf("bpp       : %u\n", info.bits_per_pixel);
	printf("comp      : %u\n", info.compression);
	printf("img size  : %u\n", info.img_size);
}

void				print_pixel(t_pixel pixel)
{
	printf("( %u ", (unsigned int)pixel.red);
	printf("%u ", (unsigned int)pixel.green);
	printf("%u )", (unsigned int)pixel.blue);
}
