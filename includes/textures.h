#ifndef TEXTURES_H
# define TEXTURES_H

#include <stdlib.h>

#define NUM_OF_GROCERIES 7

# define APPLE		1
# define BACON		2
# define CHERRY		3
# define JARS		4
# define WATER		5
# define WINE		6
# define SODA		7

#define SPR_APPLE	"sprites/groceries/butter.bmp"
#define SPR_BACON	"sprites/groceries/brinta.bmp"
#define SPR_CHERRY	"sprites/walls/tony1.bmp"
#define SPR_JARS	"sprites/walls/douwe.bmp"
#define SPR_SODA	"sprites/groceries/mayonaisse.bmp"
#define SPR_WATER	"sprites/groceries/kellogs.bmp"
#define SPR_WINE	"sprites/groceries/chocolate_milk.bmp"

#define TEX_APPLE	"textures/walls/apple.bmp"
#define TEX_BACON	"textures/walls/sausage_bacon.bmp"
#define TEX_CHERRY	"textures/walls/cherry-strawberry.bmp"
#define TEX_JARS	"textures/walls/jar-wall.bmp"
#define TEX_SODA	"textures/walls/soda.bmp"
#define TEX_WATER	"textures/walls/water.bmp"
#define TEX_WINE	"textures/walls/wine.bmp"

typedef struct s_doom	t_doom;
typedef struct s_item	t_item;

typedef struct			s_grocery_paths {
	const char			*path_shelf;
	const char			*path_sprite;
	uint8_t				type;
}						t_grocery_paths;

static const t_grocery_paths GROCERIE_PATHS[] = {
	{TEX_APPLE, SPR_APPLE, APPLE},
	{TEX_BACON, SPR_BACON, BACON},
	{TEX_CHERRY, SPR_CHERRY, CHERRY},
	{TEX_JARS, SPR_JARS, JARS},
	{TEX_SODA, SPR_SODA, SODA},
	{TEX_WINE, SPR_WINE, WINE},
	{TEX_WATER, SPR_WATER, WATER}
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
