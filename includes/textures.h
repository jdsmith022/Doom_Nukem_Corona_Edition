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

#define NUM_OF_GROCERIES 5

#define SPR_BACON	"textures/groceries/brinta.bmp"
#define SPR_APPLE	"textures/groceries/butter.bmp"
#define SPR_WINE	"textures/groceries/chocolate_milk.bmp"
#define SPR_WATER	"textures/groceries/kellogs.bmp"
#define SPR_SODA	"textures/groceries/mayonaisse.bmp"

#define TEX_BACON	"textures/walls/sausage_bacon.bmp"
#define TEX_APPLE	"textures/walls/apple.bmp"
#define TEX_WINE	"textures/walls/wine.bmp"
#define TEX_WATER	"textures/walls/water.bmp"
#define TEX_SODA	"textures/walls/soda.bmp"

typedef struct s_doom	t_doom;
typedef struct s_item	t_item;

typedef struct			s_grocery_paths {
	const char			*path_shelf;
	const char			*path_sprite;
	uint8_t				type;
}						t_grocery_paths;

static const t_grocery_paths GROCERIE_PATHS[] = {
	{TEX_WATER, SPR_WATER, WATER},
	{TEX_APPLE, SPR_APPLE, APPLE},
	{TEX_WINE, SPR_WINE, WINE},
	{TEX_SODA, SPR_SODA, SODA},
	{TEX_BACON, SPR_BACON, BACON}
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
