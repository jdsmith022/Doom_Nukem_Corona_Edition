#ifndef TEXTURES_H
# define TEXTURES_H

#include <stdlib.h>

#define NUM_OF_GROCERIES 40

# define APPLE		1
# define BACON		2
# define CHERRY		3
# define JAM		4
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
# define ALCOHOL	24
# define WINE2		25
# define WINE3		26
# define TART		27
# define BUTTER		28
# define PIE_CHERRY	29
# define PIE_LEMON	30
# define KETCHUP	31
# define TOMATO		32
# define CHOCOLATE	33
# define KIWI		34
# define OLIVE		35
# define CUCUMBER	36
# define PAPRIKA	37
# define MARMELADE	38
# define STEAK		39
# define BROWNIE	40
# define BOX		41
# define MILK		42
# define SPRAY		43
# define JARS1		44
# define JARS2		45
# define JARS3		46
# define JARS4		47

#define TEX_APPLE	"assets/textures/shelves/apple.bmp"
#define TEX_BACON	"assets/textures/shelves/sausage_bacon.bmp"
#define TEX_CHERRY	"assets/textures/shelves/cherry_strawberry.bmp"
#define TEX_JAM		"assets/textures/shelves/jar6.bmp"
#define TEX_COLA	"assets/textures/shelves/soda2.bmp"
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
#define SPR_JAM		"assets/sprites/groceries/jam.bmp"
#define SPR_COLA	"assets/sprites/groceries/cola.bmp"
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
	{TEX_JAM, SPR_JAM, JAM},
	{TEX_COLA, SPR_COLA, SODA},
	{TEX_WATER, SPR_WATER, WATER},
	{TEX_WINE, SPR_WINE, WINE},
	{TEX_CHEESE, SPR_CHEESE, CHEESE},
	{TEX_COOKIE, SPR_COOKIE, COOKIE},
	{
		"assets/textures/shelves/bread.bmp", 
		"assets/sprites/groceries/bread.bmp", 
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
		"assets/sprites/groceries/jerky.bmp",
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
		"assets/textures/shelves/citrus2.bmp",
		"assets/sprites/groceries/lemon.bmp",
		LEMON
	},
	{
		"assets/textures/shelves/alcohol.bmp",
		"assets/sprites/groceries/whiskey.bmp",
		ALCOHOL
	},
	{
		"assets/textures/shelves/wine1.bmp",
		"assets/sprites/groceries/wine2.bmp",
		WINE2
	},
	{
		"assets/textures/shelves/wine2.bmp",
		"assets/sprites/groceries/wine3.bmp",
		WINE3
	},
	{
		"assets/textures/shelves/tarts.bmp",
		"assets/sprites/groceries/tart.bmp",
		TART
	},
	{
		"assets/textures/shelves/butter.bmp",
		"assets/sprites/groceries/butter.bmp",
		BUTTER
	},
	{
		"assets/textures/shelves/pie1.bmp",
		"assets/sprites/groceries/cherry_pie.bmp",
		PIE_CHERRY
	},
	{
		"assets/textures/shelves/pie2.bmp",
		"assets/sprites/groceries/lemon_pie.bmp",
		PIE_LEMON
	},
	{
		"assets/textures/shelves/sauces.bmp",
		"assets/sprites/groceries/ketchup.bmp",
		KETCHUP
	},
	{
		"assets/textures/shelves/veggies.bmp",
		"assets/sprites/groceries/tomato.bmp",
		TOMATO
	},
	{
		"assets/textures/shelves/chocolate.bmp",
		"assets/sprites/groceries/tony1.bmp",
		CHOCOLATE
	},
	{
		"assets/textures/shelves/fruit.bmp",
		"assets/sprites/groceries/kiwi.bmp",
		KIWI
	},
	{
		"assets/textures/shelves/veggies2.bmp",
		"assets/sprites/groceries/olive.bmp",
		OLIVE
	},
	{
		"assets/textures/shelves/veggies3.bmp",
		"assets/sprites/groceries/cucumber.bmp",
		CUCUMBER
	},
	{
		"assets/textures/shelves/paprika.bmp",
		"assets/sprites/groceries/red_paprika.bmp",
		PAPRIKA
	},
	{
		"assets/textures/shelves/jar5.bmp",
		"assets/sprites/groceries/marmelade.bmp",
		MARMELADE
	},
	{
		"assets/textures/shelves/beef.bmp",
		"assets/sprites/groceries/steak.bmp",
		STEAK
	},
	{
		"assets/textures/shelves/sweets.bmp",
		"assets/sprites/groceries/brownie.bmp",
		BROWNIE
	},
	{
		"assets/textures/shelves/boxes.bmp",
		"assets/sprites/groceries/box.bmp",
		BOX
	},
	{
		"assets/textures/shelves/milk.bmp",
		"assets/sprites/groceries/milk1.bmp",
		MILK
	},
	{
		"assets/textures/shelves/milk2.bmp",
		"assets/sprites/groceries/milk1.bmp",
		MILK
	},
	{
		"assets/textures/shelves/milk3.bmp",
		"assets/sprites/groceries/milk1.bmp",
		MILK
	},
	{
		"assets/textures/shelves/spray_bottles.bmp",
		"assets/sprites/groceries/spray_bottle.bmp",
		SPRAY
	},
	{
		"assets/textures/shelves/jar1.bmp",
		"assets/sprites/groceries/glass_jar2.bmp",
		JARS1
	},
	{
		"assets/textures/shelves/jar2.bmp",
		"assets/sprites/groceries/glass_jar4.bmp",
		JARS2
	},
	{
		"assets/textures/shelves/jar3.bmp",
		"assets/sprites/groceries/glass_jar8.bmp",
		JARS3
	},
	{
		"assets/textures/shelves/jar4.bmp",
		"assets/sprites/groceries/glass_jar6.bmp",
		JARS4
	}
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
