# BMP Reader

Simple BMP reader. Only works for uncompressed 24-bit bmp files.

## Compiling

```
make
gcc [ c_file ] lib_bmp.a libft/libft.a
```

## Read BMP example
```
t_bmp	bmp;
int		fd;

fd = open('example.bmp', O_RDONLY);

// Reads BMP into t_bmp struct
bmp = read_bmp(fd);

// Prints some info about the image
print_meta_data(bmp.info);

```

## t_bmp struct

This struct gets returned by read_bmp() and has all the pixels and a pointer to t_bmp_info

```
typedef struct		s_bmp
{
	t_bmp_info		info;
	t_pixel			*pixels;
}					t_bmp;

```

## t_bmp_info

This struct contains info about the image
NOTE: img_size only represents compressed image size. If there is no compression, img_size will be 0.
to get the actual dimensions of the image in pixels, use:

```
size = bmp.info.width * bmp.info.height
```

```
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

```

## t_pixel

This struct represents a 3-byte pixel

```
typedef struct		s_pixel
{
	uint8_t 		red;
	uint8_t 		green;
	uint8_t 		blue;
}					t_pixel;
```
