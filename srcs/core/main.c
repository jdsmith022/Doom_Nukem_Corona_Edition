
#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"

int	main(void)
{
	t_doom	doom;
 	ft_bzero(&doom, sizeof(t_doom));
	sdl_init(&doom);
	sleep(10);
	save_libraries(&doom);

	// while (1);
	save_font_libraries(&doom);
	doom_init(&doom);
	// doom_start(&doom);
	game_loop(&doom);
	return (0);
}
