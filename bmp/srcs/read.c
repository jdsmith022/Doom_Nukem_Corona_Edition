#include "bmp.h"

// t_bmp		read_bmp(int fd)
// Input: valid file descriptor
// Return: t_bmp struct containing info about the image and a 2d array of pixels in t_bmp.pixels

static bool			end_of_row(uint32_t width, uint32_t current)
{
	if (current % width == 0)
		return true;
	return false;
}

static void			read_pixels(t_bmp *bmp, int fd)
{
	uint8_t			swap;
	uint8_t			padding;
	uint8_t			temp[4];
	uint32_t 		i;

	padding = ((bmp->info.width * 3) % 4);
	padding = padding ? 4 - padding : padding;
	i = 0;
	while (i < bmp->info.height * bmp->info.width){
		read(fd, &bmp->pixels[i], bmp->info.bits_per_pixel / 8);
		swap = bmp->pixels[i].blue;
		bmp->pixels[i].blue = bmp->pixels[i].red;
		bmp->pixels[i].red = swap;
		i++;
		if (padding && end_of_row(bmp->info.width, i))
			read(fd, temp, padding);
	}
	return ;
}

static void			swap_rows(t_bmp *bmp)
{
	uint32_t		i;
	uint32_t		opposite_row;
	uint32_t		pixels_to_swap;
	t_pixel			swap;

	i = 0;
	pixels_to_swap = bmp->info.height / 2 * bmp->info.width;
	opposite_row = bmp->info.height - 1;
	while (i < pixels_to_swap)
	{
		swap = bmp->pixels[i];
		bmp->pixels[i] = bmp->pixels[i + (opposite_row * bmp->info.width)];
		bmp->pixels[i + (opposite_row * bmp->info.width)] = swap;
		i++;
		if (end_of_row(bmp->info.width, i))
			opposite_row -= 2;
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
	bmp.pixels = ft_memalloc(bmp.info.height * bmp.info.width * sizeof(t_pixel)); // alloc pixels
	read_pixels(&bmp, fd); // Read pixels
	swap_rows(&bmp);
	return bmp;
}
