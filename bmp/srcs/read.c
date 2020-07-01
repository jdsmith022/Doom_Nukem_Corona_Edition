#include "bmp.h"

static void			swap_rows(t_bmp *bmp, uint8_t padding)
{
	void		*temp;
	void		*last_row;
	uint32_t	row_width;
	uint32_t	i;

	row_width = (bmp->info.width * 3) + padding;
	temp = ft_memalloc(sizeof(void *) * row_width);
	i = 0;
	while (i < bmp->info.height / 2)
	{
		last_row = bmp->pixels + (bmp->info.height - (1 + i)) * row_width;
		ft_memcpy(temp, bmp->pixels + (i * row_width), row_width);
		ft_memcpy(bmp->pixels + (i * row_width), last_row, row_width);
		ft_memcpy(last_row, temp, row_width);
		i++;
	}
	free(temp);
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
	swap_rows(bmp, padding);
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
	return bmp;
}
