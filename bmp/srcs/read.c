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
	uint8_t			padding;

	padding = ((bmp->info.width * 3) % 4);
	padding = padding ? 4 - padding : padding;
	bmp->info.img_size = bmp->info.height * bmp->info.width;
	bmp->info.img_size *= (bmp->info.bits_per_pixel / 8);
	bmp->info.img_size += (padding * bmp->info.height);
	bmp->pixels = (void *)ft_memalloc(bmp->info.img_size); // alloc pixels
	read(fd, bmp->pixels, bmp->info.img_size);
	return ;
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
	read_pixels(&bmp, fd); // Read pixels
	// swap_rows(&bmp);
	return bmp;
}
