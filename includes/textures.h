#ifndef TEXTURES_H
# define TEXTURES_H

#include <stdlib.h>

#define NUM_OF_GROCERIES 7

# define APPLE		1
# define BACON		2
# define CHERRY		3
# define JARS		4
# define SODA		5
# define WATER		6
# define WINE		7

#define TEX_APPLE	"assets/textures/shelves/apple.bmp"
#define TEX_BACON	"assets/textures/shelves/sausage_bacon.bmp"
#define TEX_CHERRY	"assets/textures/shelves/cherry-strawberry.bmp"
#define TEX_JARS	"assets/textures/shelves/jar-wall.bmp"
#define TEX_SODA	"assets/textures/shelves/soda.bmp"
#define TEX_WATER	"assets/textures/shelves/water.bmp"
#define TEX_WINE	"assets/textures/shelves/wine.bmp"

#define SPR_APPLE	"assets/sprites/groceries/butter.bmp"
#define SPR_BACON	"assets/sprites/groceries/bacon.bmp"
#define SPR_CHERRY	"assets/sprites/groceries/cherry.bmp"
#define SPR_JARS	"assets/sprites/groceries/jam.bmp"
#define SPR_SODA	"assets/sprites/groceries/mayonaisse.bmp"
#define SPR_WATER	"assets/sprites/groceries/water.bmp"
#define SPR_WINE	"assets/sprites/groceries/wine1.bmp"

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
	{TEX_WATER, SPR_WATER, WATER},
	{TEX_WINE, SPR_WINE, WINE}
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
