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
	save_libraries(&doom);
	int i;
	i = 0;
	while (i < doom.lib.len_sidedef)
	{
		printf("id = %d	| sector = %d	| portal = %d	| %f, %f - %f, %f\n", doom.lib.sidedef[i].id, doom.lib.sidedef[i].sector, doom.lib.sidedef[i].opp_sector, doom.lib.sidedef[i].line.start.x, doom.lib.sidedef[i].line.start.y, doom.lib.sidedef[i].line.end.x, doom.lib.sidedef[i].line.end.y);
		i++;
	}
	save_font_libraries(&doom);
	doom_init(&doom);
	printf("%f, %f\n", doom.pos.x, doom.pos.y);
	doom_start(&doom);
	game_loop(&doom);
	return (0);
}
