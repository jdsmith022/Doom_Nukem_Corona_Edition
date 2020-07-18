#ifndef TEXTURES_H
# define TEXTURES_H

#include <stdlib.h>

# define APPLE		1
# define ORANGE		2
# define BANANA		3
# define PINEAPPLE	4
# define CHOCOLADE	5
# define SOAP		6
# define CORONA		7
# define WINE		8
# define WATER		9
# define SODA		10
# define BACON		11

#define TEX_BACON "textures/groceries/brinta.bmp"
#define TEX_APPLE "textures/groceries/butter.bmp"
#define TEX_WINE "textures/groceries/chocolate_milk.bmp"
#define TEX_WATER "textures/groceries/kellogs.bmp"
#define TEX_SODA "textures/groceries/mayonaisse.bmp"

#define WALL_BACON "textures/walls/sausage_bacon.bmp"
#define WALL_APPLE "textures/walls/apple.bmp"
#define WALL_WINE "textures/walls/wine.bmp"
#define WALL_WATER "textures/walls/water.bmp"
#define WALL_SODA "textures/walls/soda.bmp"

#define GROCERY_LENGTH 5
# define SHOPPING_LIST_LENGTH 1

typedef struct	s_grocery_paths {
	const char	*path_shelf;
	const char	*path_sprite;
	uint8_t		type;
}				t_grocery_paths;

static const t_grocery_paths grocerie_paths[] = {
	{TEX_WATER, WALL_WATER, WATER},
	{TEX_APPLE, WALL_APPLE, APPLE},
	{TEX_WINE, WALL_WINE, WINE},
	{TEX_SODA, WALL_SODA, SODA},
	{TEX_BACON, WALL_BACON, BACON}
};

#endif
