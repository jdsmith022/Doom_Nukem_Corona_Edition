#include "srcs/bmp.h"

int main(int argc, char **argv)
{
	int		fd;
	t_bmp	bmp;

	fd = open(argv[1], O_RDONLY);
	bmp = read_bmp(fd);
	print_meta_data(bmp.info);
	int i;
	i = 0;
	while (i < bmp.info.height * bmp.info.width)
	{
		print_pixel(bmp.pixels[i]);
		i++;
		if (i % (bmp.info.width) == 0)
			printf("\n");
	}
	return (0);
}
