#include "bmp.h"

// t_bmp		read_bmp(int fd)
// Input: valid file descriptor
// Return: t_bmp struct containing info about the image and a 2d array of pixels in t_bmp.pixels

static void			read_pixels(t_bmp *bmp, int fd)
{
	uint8_t			swap;
	uint8_t			padding;
	uint8_t			temp[4];
	uint32_t 		i;
	uint32_t 		j;

	padding = ((bmp->info.width * 3) % 4);
	padding = padding ? 4 - padding : padding;
	i = 0;
	while (i < bmp->info.height){
		j = 0;
		while (j < bmp->info.width){
			read(fd, &bmp->pixels[i][j], bmp->info.bits_per_pixel / 8);
			swap = bmp->pixels[i][j].blue;
			bmp->pixels[i][j].blue = bmp->pixels[i][j].red;
			bmp->pixels[i][j].red = swap;
			j++;
		}
		if (padding) read(fd, temp, padding);
		i++;
	}
	return ;
}

static void			reverse_rows(t_bmp *bmp)
{
	uint32_t		i;
	t_pixel			*swap;

	i = 0;
	while (i < bmp->info.height / 2){
		swap = bmp->pixels[i];
		bmp->pixels[i] = bmp->pixels[bmp->info.height - 1 - i];
		bmp->pixels[bmp->info.height - 1 - i] = swap;
		i++;
	}
}

t_bmp				read_bmp(int fd)
{
	t_bmp_header 	header;
	t_bmp			bmp;
	uint32_t		i;

	read(fd, &header, sizeof(t_bmp_header)); // Reads header
	if (header.signature != 0x4D42)
		exit_with_error("Error: not a bmp file.\n");
	read(fd, &(bmp.info), sizeof(t_bmp_info)); // Reads bmp info
	if (bmp.info.bits_per_pixel != 24)
		exit_with_error("Error: only supports 24bit bmp.\n");
	bmp.pixels = ft_memalloc(bmp.info.height * sizeof(t_pixel *)); // alloc pixels
	i = 0;
	while (i < bmp.info.height)
	{
		bmp.pixels[i] = ft_memalloc(bmp.info.width * sizeof(t_pixel));
		i++;
	}
	read_pixels(&bmp, fd); // Read pixels
	reverse_rows(&bmp); // Swap to get the right order
	return bmp;
}
