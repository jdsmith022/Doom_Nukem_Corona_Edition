
#include "../../includes/doom.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

static void		free_font_lib(t_doom *doom)
{
	if (doom->lib.font_lib.game_editor_font)
		void_free_lib(doom->lib.font_lib.game_editor_font);
	if (doom->lib.font_lib.hud_font)
		void_free_lib(doom->lib.font_lib.hud_font);
	if (doom->lib.font_lib.start_menu_font)
		void_free_lib(doom->lib.font_lib.start_menu_font);
	if (doom->lib.font_lib.setting_menu_font)
		void_free_lib(doom->lib.font_lib.setting_menu_font);
	if (doom->lib.font_lib.game_over_font)
		void_free_lib(doom->lib.font_lib.game_over_font);
	if (doom->lib.font_lib.instruction_font)
		void_free_lib(doom->lib.font_lib.instruction_font);
}

static void		free_game_design_lib(t_doom *doom)
{
	if (doom->game_design.sector)
		void_free_lib(doom->game_design.sector);
	if (doom->game_design.sidedef)
		void_free_lib(doom->game_design.sidedef);
}

void			free_struct_lib(t_doom *doom)
{
	if (doom->lib.sector != NULL)
		void_free_lib(doom->lib.sector);
	if (doom->lib.sidedef)
		void_free_lib(doom->lib.sidedef);
	if (doom->lib.sprites)
		void_free_lib(doom->lib.sprites);
	if (doom->groceries)
		void_free_lib(doom->groceries);
	if (doom->hud)
		void_free_lib(doom->hud);
	if (doom->menu)
		void_free_lib(doom->menu);
	free_font_lib(doom);
	free_game_design_lib(doom);
}
