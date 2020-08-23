#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"

int	main(void)
{
	t_doom	doom;

	srand(time(NULL));
	ft_bzero(&doom, sizeof(t_doom));
	ft_bzero(&doom, sizeof(t_doom));
	if (sdl_init(&doom) != 0)
		doom_exit_failure(&doom, "unable to initialize SDL\n");
	save_libraries(&doom);
	printf("id = %d, sector = %d -- %f, %f\n", doom.lib.sidedef[24].id, doom.lib.sidedef[24].sector, doom.lib.sidedef[24].line.start.x, doom.lib.sidedef[24].line.start.y);
	save_font_libraries(&doom);
	doom_init(&doom);
	doom_start(&doom);
	game_loop(&doom);
	return (0);
}
