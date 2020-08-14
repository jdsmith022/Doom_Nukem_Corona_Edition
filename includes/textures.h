#ifndef TEXTURES_H
# define TEXTURES_H

#include <stdlib.h>

#define NUM_OF_GROCERIES 23

# define APPLE		1
# define BACON		2
# define CHERRY		3
# define JARS		4
# define SODA		5
# define WATER		6
# define WINE		7
# define CHEESE		8
# define COOKIE		9
# define BREAD		10
# define POTATO		11
# define MELON		12
# define SOAP		13
# define ONION		14
# define PEPPER		15
# define CHICKEN	16
# define FISH		17
# define MEAT		18
# define CEREAL		19
# define TEA		20
# define GRAPES		21
# define TOILET		22
# define LEMON		23

#define TEX_APPLE	"assets/textures/shelves/apple.bmp"
#define TEX_BACON	"assets/textures/shelves/sausage_bacon.bmp"
#define TEX_CHERRY	"assets/textures/shelves/cherry-strawberry.bmp"
#define TEX_JARS	"assets/textures/shelves/jar-wall.bmp"
#define TEX_SODA	"assets/textures/shelves/soda.bmp"
#define TEX_WATER	"assets/textures/shelves/water.bmp"
#define TEX_WINE	"assets/textures/shelves/wine.bmp"
#define TEX_COOKIE	"assets/textures/shelves/cookies.bmp"
#define TEX_CHEESE	"assets/textures/shelves/cheese.bmp"
#define TEX_POTATO	"assets/textures/shelves/potatoes.bmp"
#define TEX_MELON	"assets/textures/shelves/melon.bmp"
#define TEX_SOAP	"assets/textures/shelves/soaps.bmp"

#define SPR_APPLE	"assets/sprites/groceries/red_apple.bmp"
#define SPR_BACON	"assets/sprites/groceries/bacon.bmp"
#define SPR_CHERRY	"assets/sprites/groceries/cherry.bmp"
#define SPR_JARS	"assets/sprites/groceries/jam.bmp"
#define SPR_SODA	"assets/sprites/groceries/cola.bmp"
#define SPR_WATER	"assets/sprites/groceries/water.bmp"
#define SPR_WINE	"assets/sprites/groceries/wine1.bmp"
#define SPR_COOKIE	"assets/sprites/groceries/Cookie.bmp"
#define SPR_CHEESE	"assets/sprites/groceries/Cheese.bmp"
#define SPR_POTATO 	"assets/sprites/groceries/potato.bmp"
#define SPR_MELON	"assets/textures/shelves/melon.bmp"
#define SPR_SOAP	"assets/sprites/groceries/soap.bmp"

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
	{TEX_WINE, SPR_WINE, WINE},
	{TEX_CHEESE, SPR_CHEESE, CHEESE},
	{TEX_COOKIE, SPR_COOKIE, COOKIE},
	{
		"assets/sprites/groceries/bread.bmp", 
		"assets/textures/shelves/bread.bmp", 
		BREAD
	},
	{TEX_POTATO, SPR_POTATO, POTATO},
	{
		"assets/textures/shelves/melon.bmp", 
		"assets/sprites/groceries/watermelon.bmp", 
		MELON
	},
	{
		"assets/textures/shelves/soaps.bmp",
		"assets/sprites/groceries/soap.bmp", 
		SOAP
	},
	{
		"assets/textures/shelves/onions.bmp",
		"assets/sprites/groceries/red_onion.bmp",
		ONION
	},
	{
		"assets/textures/shelves/peppers.bmp",
		"assets/sprites/groceries/red_pepper.bmp",
		PEPPER
	},
	{
		"assets/textures/shelves/chicken.bmp",
		"assets/sprites/groceries/chicken.bmp",
		CHICKEN
	},
	{
		"assets/textures/shelves/fish.bmp",
		"assets/sprites/groceries/fish.bmp",
		FISH
	},
	{
		"assets/textures/shelves/meat.bmp",
		"assets/sprites/groceries/steak.bmp",
		MEAT
	},
	{
		"assets/textures/shelves/cereal.bmp",
		"assets/sprites/groceries/cereal.bmp",
		CEREAL
	},
	{
		"assets/textures/shelves/tea.bmp",
		"assets/sprites/groceries/tea.bmp",
		TEA
	},
	{
		"assets/textures/shelves/grapes.bmp",
		"assets/sprites/groceries/red_grapes.bmp",
		GRAPES
	},

	{
		"assets/textures/shelves/toiletpaper.bmp",
		"assets/sprites/groceries/toiletpaper.bmp",
		TOILET
	},
	{
		"assets/textures/shelves/citrus.bmp",
		"assets/sprites/groceries/lemon.bmp",
		LEMON
	},
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
