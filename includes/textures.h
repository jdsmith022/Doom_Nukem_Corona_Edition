#ifndef TEXTURES_H
# define TEXTURES_H

# include <stdlib.h>

# define GROC_COUNT				49

typedef enum					e_groc_types {
	APPLE = 1, BACON, CHERRY, JAM,
	SODA, WATER, WINE, CHEESE,
	COOKIE, BREAD, POTATO, MELON,
	SOAP, ONION, PEPPER, CHICKEN,
	FISH, MEAT, CEREAL, TEA,
	GRAPES, TOILET, LEMON, ALCOHOL,
	WINE2, WINE3, TART, BUTTER,
	PIE_CHERRY, PIE_LEMON, KETCHUP, TOMATO,
	CHOCOLATE, KIWI, OLIVE, CUCUMBER,
	PAPRIKA, MARMELADE, STEAK, BROWNIE,
	MILK, SPRAY, JARS1, JARS2,
	JARS3, HONEY, SHRIMP
}								t_groc_types;

// # define APPLE					1
// # define BACON					2
// # define CHERRY					3
// # define JAM					4
// # define SODA					5
// # define WATER					6
// # define WINE					7
// # define CHEESE					8
// # define COOKIE					9
// # define BREAD					10
// # define POTATO					11
// # define MELON					12
// # define SOAP					13
// # define ONION					14
// # define PEPPER					15
// # define CHICKEN				16
// # define FISH					17
// # define MEAT					18
// # define CEREAL					19
// # define TEA					20
// # define GRAPES					21
// # define TOILET					22
// # define LEMON					23
// # define ALCOHOL				24
// # define WINE2					25
// # define WINE3					26
// # define TART					27
// # define BUTTER					28
// # define PIE_CHERRY				29
// # define PIE_LEMON				30
// # define KETCHUP				31
// # define TOMATO					32
// # define CHOCOLATE				33
// # define KIWI					34
// # define OLIVE					35
// # define CUCUMBER				36
// # define PAPRIKA				37
// # define MARMELADE				38
// # define STEAK					39
// # define BROWNIE				40
// # define MILK					42
// # define SPRAY					43
// # define JARS1					44
// # define JARS2					45
// # define JARS3					46
// # define HONEY					47
// # define SHRIMP					48

typedef struct s_doom			t_doom;
typedef struct s_item			t_item;

typedef struct					s_grocery_paths {
	const char					*path_shelf;
	const char					*path_sprite;
	uint8_t						type;
}								t_grocery_paths;

t_groc_types					g_types;

static const t_grocery_paths	g_groc_paths[] = {
	{
		"assets/textures/shelves/apple.bmp",
		"assets/sprites/groceries/red_apple.bmp",
		APPLE
	},
	{
		"assets/textures/shelves/sausage_bacon.bmp",
		"assets/sprites/groceries/bacon.bmp",
		BACON
	},
	{
		"assets/textures/shelves/cherry_strawberry.bmp",
		"assets/sprites/groceries/cherry.bmp",
		CHERRY
	},
	{
		"assets/textures/shelves/jar6.bmp",
		"assets/sprites/groceries/jam.bmp",
		JAM
	},
	{
		"assets/textures/shelves/soda2.bmp",
		"assets/sprites/groceries/cola.bmp",
		SODA
	},
	{
		"assets/textures/shelves/water.bmp",
		"assets/sprites/groceries/water.bmp",
		WATER
	},
	{
		"assets/textures/shelves/wine.bmp",
		"assets/sprites/groceries/wine1.bmp",
		WINE
	},
	{
		"assets/textures/shelves/cookies.bmp",
		"assets/sprites/groceries/Cookie.bmp",
		COOKIE
	},
	{
		"assets/textures/shelves/cheese.bmp",
		"assets/sprites/groceries/Cheese.bmp",
		CHEESE
	},
	{
		"assets/textures/shelves/bread.bmp",
		"assets/sprites/groceries/bread.bmp",
		BREAD
	},
	{
		"assets/textures/shelves/potatoes.bmp",
		"assets/sprites/groceries/potato.bmp",
		POTATO
	},
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
		"assets/sprites/groceries/pickled_eggs.bmp",
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
		"assets/sprites/groceries/glass_jar3.bmp",
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
		"assets/textures/shelves/potatoes.bmp",
		"assets/sprites/groceries/swee_potatoe.bmp",
		POTATO
	},
	{
		"assets/textures/shelves/round_jars.bmp",
		"assets/sprites/groceries/honey.bmp",
		HONEY
	},
	{
		"assets/textures/shelves/fish2.bmp",
		"assets/sprites/groceries/shrimp.bmp",
		SHRIMP
	}
};

void				set_sprite(t_doom *doom, uint8_t type, t_item *item);

#endif
