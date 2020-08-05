#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

int	main(void)
{
	t_doom	doom;

	srand(time(NULL));
	ft_bzero(&doom, sizeof(t_doom));
	//load_maps();
	//init_struct();
	//init_message_bus();
	if (sdl_init(&doom) != 0)
		doom_exit_failure(&doom, "unable to initialize SDL\n");
	save_libraries(&doom);
	save_font_libraries(&doom);
	doom_init(&doom);
	doom_start(&doom);
	printf("huh\n");
	game_loop(&doom);
	return (0);
}
