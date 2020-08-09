#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void game_init(t_doom *doom)
{
	srand(time(NULL));
	//load_maps();
	//init_struct();
	//init_message_bus();
	if (doom->start == TRUE)
	{
		ft_bzero(doom, sizeof(t_doom));
		if (sdl_init(doom) != 0)
			doom_exit_failure(doom, "unable to initialize SDL\n");
		save_font_libraries(doom);
	}
	printf("here\n");
	save_libraries(doom);
	printf("end\n");
	doom_init(doom);
	doom_start(doom);
	game_loop(doom);
}

int	main(void)
{
	t_doom	doom;

	// srand(time(NULL));
	// ft_bzero(&doom, sizeof(t_doom));
	ft_bzero(&doom, sizeof(t_doom));
	doom.start = TRUE;
	game_init(&doom);
	//load_maps();
	//init_struct();
	//init_message_bus();
	// if (sdl_init(&doom) != 0)
	// 	doom_exit_failure(&doom, "unable to initialize SDL\n");
	// save_libraries(&doom);
	// save_font_libraries(&doom);
	// doom_init(&doom);
	// doom_start(&doom);
	// game_loop(&doom);
	return (0);
}
