#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

int	main(void)
{
	t_doom	doom;

	srand(time(NULL));
	ft_bzero(&doom, sizeof(t_doom));
	ft_bzero(&doom, sizeof(t_doom));
	// init_message_bus();
	if (sdl_init(&doom) != 0)
		doom_exit_failure(&doom, "unable to initialize SDL\n");
	// printf("here\n");
	save_libraries(&doom);
	// printf("here0\n");
	save_font_libraries(&doom);
	// printf("here1\n");

	doom_init(&doom);
	// printf("here2\n");

	doom_start(&doom);
	// printf("here1\n");

	game_loop(&doom);
	return (0);
}
