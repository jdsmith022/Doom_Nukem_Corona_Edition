#include "srcs/bmp.h"

int main(int argc, char **argv)
{
	int		fd;
	t_bmp	bmp;

	fd = open(argv[1], O_RDONLY);
	bmp = read_bmp(fd);
	print_meta_data(bmp.info);
	return (0);
}
