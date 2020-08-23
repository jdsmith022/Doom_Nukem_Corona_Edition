#include "bmp.h"

static void			swap_rows(t_bmp *bmp, uint8_t padding)
{
	void		*temp;
	void		*last_row;
	uint32_t	row_width;
	uint32_t	i;

	row_width = (bmp->info.width * (bmp->info.bits_per_pixel / 8)) + padding;
	temp = ft_memalloc(sizeof(void *) * row_width);
	if (temp == NULL)
	{
		bmp = NULL;
		return ;
	}
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

	padding = ((bmp->info.width * bmp->info.bits_per_pixel / 8) % 4);
	padding = padding ? 4 - padding : padding;
	bmp->info.img_size = bmp->info.height * bmp->info.width;
	bmp->info.img_size *= (bmp->info.bits_per_pixel / 8);
	bmp->info.img_size += (padding * bmp->info.height);
	bmp->pixels = (void *)ft_memalloc(bmp->info.img_size);
	if (bmp->pixels == NULL)
		return ;
	read(fd, bmp->pixels, bmp->info.img_size);
	swap_rows(bmp, padding);
	return ;
}

t_bmp				read_bmp(int fd)
{
	t_bmp_header 	header;
	t_bmp			bmp;
	uint32_t		i;

	read(fd, &header, sizeof(t_bmp_header));
	if (header.signature != 0x4D42)
		exit_with_error(&bmp, "Error: not a bmp file.\n");
	read(fd, &(bmp.info), sizeof(t_bmp_info));
	if (bmp.info.info_size != 40)
		exit_with_error(&bmp, "Error: \
			bmp reader only supports BITMAPINFOHEADER files\n");
	if (bmp.info.bits_per_pixel != 24 && bmp.info.bits_per_pixel != 32)
		exit_with_error(&bmp, "Error: \
			bmp reader only supports 24 and 32bit bmp.\n");
	if (bmp.info.compression)
		exit_with_error(&bmp, "Error: \
			bmp reader only supports uncompressed files\n");
	if (bmp.info.height < 0)
		exit_with_error(&bmp, "Error: \
			bmp reader only supports bottom-up pixel format\n");
	read_pixels(&bmp, fd);
	return (bmp);
}
