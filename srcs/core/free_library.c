#include "../../includes/doom.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

void		free_struct_lib(t_doom *doom)
{
	if (doom->lib.sector)
		void_free_lib(doom->lib.sector);
	if (doom->lib.sidedef)
		void_free_lib(doom->lib.sidedef);
	if (doom->lib.sprites)
		void_free_lib(doom->lib.sprites);
	if (doom->game_design.sector)
		void_free_lib(doom->game_design.sector);
	if (doom->lib.mov_sprites)
		void_free_lib(doom->lib.mov_sprites);
	if (doom->lib.font_lib.game_editor_font)
		void_free_lib(doom->lib.font_lib.game_editor_font);
	if (doom->lib.font_lib.hud_font)
		void_free_lib(doom->lib.font_lib.hud_font);
	if (doom->lib.font_lib.start_menu_font)
		void_free_lib(doom->lib.font_lib.start_menu_font);
	if (doom->lib.font_lib.setting_menu_font)
		void_free_lib(doom->lib.font_lib.setting_menu_font);
	if (doom->hud)
		void_free_lib(doom->hud);
	if (doom->menu)
		void_free_lib(doom->menu);
	//add other font libs to be freed
}

static void		free_sld_libs(SDL_Surface **lib, int len)
{
	size_t index;

	index = 0;
	while (index < len)
	{
		ft_bzero(lib[index], sizeof(lib[index]));
		free(lib[index]);
		index++;
	}
	free(lib);
}

void		free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;
	int			len;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		len = doom->lib.len_tex_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		len = doom->lib.len_obj_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_libs(lib, len);
	}
}
