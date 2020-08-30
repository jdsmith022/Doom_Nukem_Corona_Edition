
#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"

int	main(void)
{
	t_doom	doom;

	printf("A");
	ft_bzero(&doom, sizeof(t_doom));
	printf("B");
	sdl_init(&doom);
	printf("C");
	save_libraries(&doom);
	printf("D");
	save_font_libraries(&doom);
	printf("E");
	doom_init(&doom);
	printf("F");
	doom_start(&doom);
	printf("G");
	game_loop(&doom);
	printf("H");
	return (0);
}
