#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

int	main(void)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	//load_maps();
	//init_struct();
	//init_message_bus();
	save_libraries(&doom);
	save_font_libraries(&doom);
	doom.game_editor = FALSE;
	doom_init(&doom);
	//load_default(); //loads default settings ie menu, player settings
	//init_HUD/UI
	game_loop(&doom);
	return (0);
}
