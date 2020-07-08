#include "bmp.h"

void				exit_with_error(const char *message){
	ft_putstr_fd(message, 2);
	exit(1);
}

void				print_meta_data(t_bmp_info info)
{
	ft_printf("\ninfo size : %u\n", info.info_size);
	ft_printf("width     : %u\n", info.width);
	ft_printf("height    : %u\n", info.height);
	ft_printf("planes    : %u\n", info.planes);
	ft_printf("bpp       : %u\n", info.bits_per_pixel);
	ft_printf("comp      : %u\n", info.compression);
	ft_printf("img size  : %u\n", info.img_size);
}

void				print_byte(void *byte, uint32_t len)
{
	while (len > 0)
	{
		ft_printf("%x ", *((uint8_t *)byte));
		byte++;
		len--;
	}
}
